// Copyright Epic Games, Inc. All Rights Reserved.

#include "DefenceGameUtils.h"
#include "Character/Core/RuleOfTheCharacter.h"
#include "Interface/Character/RuleCharacter.h"
#include "Engine/StaticMesh.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "Chaos/Transform.h"
#include "UObject/NoExportTypes.h"
#include "RawMesh/Public/RawMesh.h"
#include "Engine/SkeletalMesh.h"
#include "Math/Matrix.h"
#include "SkeletalRenderPublic.h"
#include "Rendering/SkeletalMeshLODRenderData.h"
#include "Rendering/SkeletalMeshRenderData.h"


ARuleOfTheCharacter* DefenceGameUtils::FindTargetRecently(const TArray<ARuleOfTheCharacter*>& InCharacters, const FVector& InLocation)
{
	//判断数组是否有效
	if (InCharacters.Num())
	{
		//设置基本参考参数
		float CharacterDistace = 99999999999.f;
		int32 CharacterIndex = INDEX_NONE;

		//对获取到的数组进行循环距离检测
		for (int32 i = 0;i<InCharacters.Num();i++)
		{
			//如果能够赋值成功
			if (ARuleOfTheCharacter* TargetCharacter = InCharacters[i])
			{
				//获取当前查询的Actor的位置
				FVector CharacterLocation = TargetCharacter->GetActorLocation();
				//计算他们的距离差距
				FVector TmpVector = CharacterLocation - InLocation;
				float TmpDistace = TmpVector.Size();

				//当距离小于当前最小距离并且目标还活着的时候
				if (TmpDistace < CharacterDistace && TargetCharacter->IsActive())
				{
					//满足条件就保存一次当前最近距离的TowerID和距离
					CharacterIndex = i;
					CharacterDistace = TmpDistace;
				}
			}

			if (CharacterIndex!=INDEX_NONE)
			{
				//返回对应目标的RuleOfTheCharacter
				return InCharacters[CharacterIndex];
			}
		}
	}
	return nullptr;
}

float Expression::CalcDamage(IRuleCharacter* Enemy, IRuleCharacter* Owner)
{
	//这里使用的伤害计算公式是
	//攻击伤害 / （（护甲/100）+ 1）
	if (Enemy&&Owner)
	{
		return Enemy->GetCharacterData().PhysicalAttack / ((Owner->GetCharacterData().Armor / 100) + 1);
	}
	return 0.f;
}



//创建一个临时的结构体  将结构体提升为一个全局的
struct FMeshTracker
{
	FMeshTracker()
		:bValidColors(false)
	{
		//初始化内存
		FMemory::Memset(bValidTexCoords, 0);
	}

	bool bValidTexCoords[MAX_MESH_TEXTURE_COORDS];  //判断是否是一个有效的UV
	bool bValidColors;		// UV对应的有效的颜色
};



//不需要前置声明，直接进行定义
bool IsValldSkeletalMeshComponent(USkeletalMeshComponent* InComponent)
{
	//MeshObject是关于骨骼模型的对象
	return InComponent&& InComponent->MeshObject && InComponent->IsVisible();
}

 
//骨骼模型转换函数
void SkeletalMeshToRawMeshes(
USkeletalMeshComponent* InComponent,
int32 InOverallMaxLODs,
const FMatrix& InComponentToWorld,
FMeshTracker & OutRawMeshTracker,
FRawMesh & OutRawMesh
)
{

	//获取LOD 0的LOD信息
	FSkeletalMeshLODInfo& ScrLODInfo = *(InComponent->SkeletalMesh->GetLODInfo(InOverallMaxLODs));

	//获取当前蒙皮的顶点
	TArray<FFinalSkinVertex> FinalVertices;
	InComponent->GetCPUSkinnedVertices(FinalVertices, InOverallMaxLODs);

	//获取当前骨骼的MeshRenderData
	FSkeletalMeshRenderData& SkeletalMeshRenderData = InComponent->MeshObject->GetSkeletalMeshRenderData();  

	//获取MeshLOD对应的renderData //存储当前点和骨骼的信息以及buffer
	FSkeletalMeshLODRenderData &LODData = SkeletalMeshRenderData.LODRenderData[InOverallMaxLODs];

	//进行所有点位的遍历，并且进行拷贝
	for (int32 VerticIndex = 0;VerticIndex<FinalVertices.Num();VerticIndex++)
	{
		//添加的内容进行了一次坐标转换，从局部坐标转为世界坐标（在矩阵中）
		OutRawMesh.VertexPositions.Add(InComponentToWorld.TransformPosition(FinalVertices[VerticIndex].Position));
	}

	//比大小，获取最小值
	const uint32 NumTexCoords = FMath::Min(LODData.StaticVertexBuffers.StaticMeshVertexBuffer.GetNumTexCoords(), (uint32)MAX_MESH_TEXTURE_COORDS);
	const int32 NumSections = LODData.RenderSections.Num(); //获得当前渲染分段数量

	FRawStaticIndexBuffer16or32Interface& IndexBuffer = *LODData.MultiSizeIndexContainer.GetIndexBuffer();

	//对获取到的Buffer进行遍历，对应多个Section进行遍历
	for (int32 SectionIndex = 0;SectionIndex<NumSections;SectionIndex++)
	{
		//获得骨骼渲染分段
		const FSkelMeshRenderSection& SkelMeshSection = LODData.RenderSections[SectionIndex];

		//检查当前的分段的材质是否是显示的，函数内部，如果不是隐藏的会返回真
		if (InComponent->IsMaterialSectionShown(SkelMeshSection.MaterialIndex, InOverallMaxLODs))  //获取LOD的MaterialIndex
		{
			const int32 NumWedges = SkelMeshSection.NumTriangles * 3;  //3个三角面组成一个Wedge（三角锥）

			//遍历当前三角锥，然后获取顶点索引对应的三角锥。
			for (int32 WedgeIndex = 0;WedgeIndex<NumWedges;WedgeIndex++)
			{
				const int32 VertexIndexForWedge = IndexBuffer.Get(SkelMeshSection.BaseIndex + WedgeIndex);
				OutRawMesh.WedgeIndices.Add(VertexIndexForWedge);  //获取到对应的三角锥ID，然后将这个ID添加到索引数组里

				//这里获取到蒙皮的顶点，通过他来获取当前切线的X和Z轴向的切线
				const FFinalSkinVertex& SkinnedVertex = FinalVertices[VertexIndexForWedge];

				//获取当前骨骼的皮肤顶点切线(局部空间转换为世界空间)
				//这里的SkinnedVertex.TangentX.ToFVector()是舍弃的矩阵的齐次坐标，然后直接转为XYZ的Vector
				const FVector TangentX = InComponentToWorld.TransformVector(SkinnedVertex.TangentX.ToFVector());
				const FVector TangentZ = InComponentToWorld.TransformVector(SkinnedVertex.TangentZ.ToFVector());

				//获取Z轴向的矩阵计算值（要用到他的W:齐次坐标）
				const FVector4 UnpackedTangentZ = SkinnedVertex.TangentZ.ToFVector4();

				//通过计算 X轴向和Z轴向 的叉乘（得到垂直X和Z的Y向量），来获取当前Y的长度				
				const FVector TangentY = (TangentZ ^ TangentX).GetSafeNormal() * UnpackedTangentZ.W;
				//计算方式就是 X = X / W ， Y = Y / W
				
				OutRawMesh.WedgeTangentX.Add(TangentX);
				OutRawMesh.WedgeTangentY.Add(TangentY);
				OutRawMesh.WedgeTangentZ.Add(TangentZ);

				// MAX_MESH_TEXTURE_COORDS = 8
				//接下来进行UV的遍历，将UV从skeletalMesh转到StaticMesh当中
				for (uint32 TexCoordIndex = 0;TexCoordIndex<MAX_MESH_TEXTURE_COORDS;TexCoordIndex++)
				{
					//如果当前的UV值大于最小的UV Index
					if (TexCoordIndex >= NumTexCoords)
					{
						//如果值大的话，添加一个默认空间，用作缓冲
						OutRawMesh.WedgeTexCoords[TexCoordIndex].AddDefaulted();
					}
					else
					{
						//添加对应的LODData的UV
						OutRawMesh.WedgeTexCoords[TexCoordIndex].Add
						(LODData.StaticVertexBuffers.StaticMeshVertexBuffer.GetVertexUV(VertexIndexForWedge, TexCoordIndex));

						//添加后设置Tracker为True
						OutRawMeshTracker.bValidTexCoords[TexCoordIndex] = true;
					}
				}

				//判断当前顶点着色是否已经初始化，如果初始化就进行添加
				if (LODData.StaticVertexBuffers.ColorVertexBuffer.IsInitialized())
				{
					OutRawMesh.WedgeColors.Add(LODData.StaticVertexBuffers.ColorVertexBuffer.VertexColor(VertexIndexForWedge));
					OutRawMeshTracker.bValidColors = true;
				}
				else
				{
					//没有初始化就自动填充一个白色
					OutRawMesh.WedgeColors.Add(FColor::White);
				}
			}

			//开始处理材质
			int32 MaterialIndex = SkelMeshSection.MaterialIndex;
			//判断当前Index的材质是否是有效的
			if (ScrLODInfo.LODMaterialMap.IsValidIndex(SectionIndex)&& ScrLODInfo.LODMaterialMap[SectionIndex]!=INDEX_NONE)
			{
				//如果材质有效就重新映射材质索引(范围是0 - 骨骼模型的最多材质数量)
				//ScrLODInfo.LODMaterialMap 这里面放着所有材质的索引
				//如果Index超过范围了，那么就会被裁剪
				MaterialIndex = FMath::Clamp<int32>(ScrLODInfo.LODMaterialMap[SectionIndex], 0, InComponent->SkeletalMesh->Materials.Num());

			}

			//最后拿到材质后开始进行遍历Copy
			for (uint32 TriIndex = 0;TriIndex<SkelMeshSection.NumTriangles;TriIndex++)
			{
				OutRawMesh.FaceMaterialIndices.Add(MaterialIndex);
				OutRawMesh.FaceSmoothingMasks.Add(0);  //设置0，直接忽略这个值
			}

		}
	}

}


UStaticMesh* MeshUtils::SkeletalCompToStaticMesh(UWorld* World, USkeletalMeshComponent* SkeletalMeshComp)
{
	//创建临时Mesh变量
	UStaticMesh* TempStaticMesh = nullptr;


	//创建一个原始数据的数组（这是和图形相关的一个数据，有空可以看看）
	FRawMesh TargetRawMesh;
	FMeshTracker MeshTracker;
	int32 OverallMaxLODs = 0;  //只需要第一层的那个LOD的模型转换为绿色模型即可


	//初始化一个临时位置
	const FTransform& InRootTransform = FTransform::Identity; //默认单位Transform(W = 1)

	FMatrix WorldToRoot = InRootTransform.ToMatrixWithScale().Inverse();  //获得单位矩阵
	//旋转后如果想要撤销，那么就乘以他的逆即可。（Inverse)
	
	//计算得到当前组件与世界的矩阵
	FMatrix ComponentToWorld = SkeletalMeshComp->GetComponentTransform().ToMatrixWithScale() * WorldToRoot;

	
	if (IsValldSkeletalMeshComponent(SkeletalMeshComp))
	{
		//调用转换函数
		/** 
		1、输入骨骼组件
		2、输入需要获取的LOD = 0
		3、输入对应的组件转出的世界坐标
		4、获取返回的MeshTracker
		5、获取返回的RawMesh
		*/
		SkeletalMeshToRawMeshes(SkeletalMeshComp, OverallMaxLODs, ComponentToWorld, MeshTracker, TargetRawMesh);
	}

	//清除无效的顶点颜色和纹理坐标
	uint32 MaxInUseTextureCoordiante = 0;

	//判断当前颜色是否有效
	if (!MeshTracker.bValidColors)
	{
		//如果无效就直接清空
		TargetRawMesh.WedgeColors.Empty();
	}
	
	//遍历当前的纹理坐标(uv)
	for (uint32 TexCoordIndex = 0;TexCoordIndex<MAX_MESH_TEXTURE_COORDS;TexCoordIndex++ )
	{
		if (!MeshTracker.bValidTexCoords[TexCoordIndex])
		{
			//Current TexCoord isn't Valid
			TargetRawMesh.WedgeTexCoords[TexCoordIndex].Empty();
		}
		else
		{
			//如果有效就获取到最大使用的贴图坐标。
			MaxInUseTextureCoordiante = FMath::Max(MaxInUseTextureCoordiante, TexCoordIndex);
		}
	}


	//判断当前RawMesh是否是有意义的
	if (TargetRawMesh.IsValidOrFixable())
	{
		//初始ID名称，并创建一个Mesh 
		FString MeshName = FGuid::NewGuid().ToString();

		//使用RF_Transient 是为了告诉World，这个模型不需要进行序列化到磁盘，只是在游戏中进行使用。
		TempStaticMesh = NewObject<UStaticMesh>(World, *MeshName, RF_Transient);  //创建一个Mesh

		TempStaticMesh->InitResources();  // 初始化Mesh资源

		//生成光照的GUID
		TempStaticMesh->LightingGuid = FGuid::NewGuid();
		
		//获取当前灯光贴图，也就是默认比当前的模型坐标ID+1 就是UV的光照坐标。（1-7）
		//MaxInUseTextureCoordiante = 0号默认就是物体本身的材质
		const uint32 LightMapIndex = FMath::Min(MaxInUseTextureCoordiante+1,(uint32)8 -1);


		//部署可以渲染为静态模型的模型源。

		//首先获取静态模型源
		FStaticMeshSourceModel& SrcModel = TempStaticMesh->AddSourceModel();

		//无需重新计算网格中的发现，所以忽略计算
		SrcModel.BuildSettings.bRecomputeNormals = false;

		//切线也无需计算
		SrcModel.BuildSettings.bRecomputeTangents = false;

		//移除无法生成的三角形
		SrcModel.BuildSettings.bRemoveDegenerates = true;

		// 关闭以十六位对八位的精度来进行储存(Precision = 精度)
		SrcModel.BuildSettings.bUseHighPrecisionTangentBasis = false;

		// 是否要用全浮点精度来存储UV（不必要）,GPU计算会很慢
		SrcModel.BuildSettings.bUseFullPrecisionUVs = false;

		// 是否生成灯光贴图,把模型做好后会自动烘焙一个
		SrcModel.BuildSettings.bGenerateLightmapUVs = true;

		// 灯光贴图ID为0 
		SrcModel.BuildSettings.SrcLightmapIndex = 0;

		// 目标光照图索引 = 灯光贴图索引（计算所得的那个）
		SrcModel.BuildSettings.DstLightmapIndex = LightMapIndex;

		//将rawmesh数据添加到结构中
		SrcModel.SaveRawMesh(TargetRawMesh);

		//将导入的版本设置为上一次保存的版本
		TempStaticMesh->ImportVersion = EImportStaticMeshVersion::LastVersion;

		//设置光照贴图索引 = 计算所得
		TempStaticMesh->LightMapCoordinateIndex = LightMapIndex;


		//创建一个材质索引（唯一的）
		TArray<int32> UniqueMaterialIndices;
		for (int32 MaterialIndex: TargetRawMesh.FaceMaterialIndices)  //对当前材质进行遍历
		{
			UniqueMaterialIndices.AddUnique(MaterialIndex);
		}

		// 对材质进行遍历
		for (int32 i = 0; i<UniqueMaterialIndices.Num() ;i++)
		{
			//设置当前LOD，目前只设置1个，所以为0， 如果有很多LOD的话，对LOD进行遍历即可
			// 针对材质进行设置信息
			//设置对应的SectionInfo
			TempStaticMesh->GetSectionInfoMap().Set(0,i,FMeshSectionInfo(UniqueMaterialIndices[i]));
		}

		//获取对应的原始Section map（截面）,将当前Section Map拷贝为原始Section Map
		TempStaticMesh->GetOriginalSectionInfoMap().CopyFrom(TempStaticMesh->GetSectionInfoMap());

		//对当前模型进行烘焙
		TempStaticMesh->Build(false);

	}

	return TempStaticMesh;
}
