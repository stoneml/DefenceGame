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
	//�ж������Ƿ���Ч
	if (InCharacters.Num())
	{
		//���û����ο�����
		float CharacterDistace = 99999999999.f;
		int32 CharacterIndex = INDEX_NONE;

		//�Ի�ȡ�����������ѭ��������
		for (int32 i = 0;i<InCharacters.Num();i++)
		{
			//����ܹ���ֵ�ɹ�
			if (ARuleOfTheCharacter* TargetCharacter = InCharacters[i])
			{
				//��ȡ��ǰ��ѯ��Actor��λ��
				FVector CharacterLocation = TargetCharacter->GetActorLocation();
				//�������ǵľ�����
				FVector TmpVector = CharacterLocation - InLocation;
				float TmpDistace = TmpVector.Size();

				//������С�ڵ�ǰ��С���벢��Ŀ�껹���ŵ�ʱ��
				if (TmpDistace < CharacterDistace && TargetCharacter->IsActive())
				{
					//���������ͱ���һ�ε�ǰ��������TowerID�;���
					CharacterIndex = i;
					CharacterDistace = TmpDistace;
				}
			}

			if (CharacterIndex!=INDEX_NONE)
			{
				//���ض�ӦĿ���RuleOfTheCharacter
				return InCharacters[CharacterIndex];
			}
		}
	}
	return nullptr;
}

float Expression::CalcDamage(IRuleCharacter* Enemy, IRuleCharacter* Owner)
{
	//����ʹ�õ��˺����㹫ʽ��
	//�����˺� / ��������/100��+ 1��
	if (Enemy&&Owner)
	{
		return Enemy->GetCharacterData().PhysicalAttack / ((Owner->GetCharacterData().Armor / 100) + 1);
	}
	return 0.f;
}



//����һ����ʱ�Ľṹ��  ���ṹ������Ϊһ��ȫ�ֵ�
struct FMeshTracker
{
	FMeshTracker()
		:bValidColors(false)
	{
		//��ʼ���ڴ�
		FMemory::Memset(bValidTexCoords, 0);
	}

	bool bValidTexCoords[MAX_MESH_TEXTURE_COORDS];  //�ж��Ƿ���һ����Ч��UV
	bool bValidColors;		// UV��Ӧ����Ч����ɫ
};



//����Ҫǰ��������ֱ�ӽ��ж���
bool IsValldSkeletalMeshComponent(USkeletalMeshComponent* InComponent)
{
	//MeshObject�ǹ��ڹ���ģ�͵Ķ���
	return InComponent&& InComponent->MeshObject && InComponent->IsVisible();
}

 
//����ģ��ת������
void SkeletalMeshToRawMeshes(
USkeletalMeshComponent* InComponent,
int32 InOverallMaxLODs,
const FMatrix& InComponentToWorld,
FMeshTracker & OutRawMeshTracker,
FRawMesh & OutRawMesh
)
{

	//��ȡLOD 0��LOD��Ϣ
	FSkeletalMeshLODInfo& ScrLODInfo = *(InComponent->SkeletalMesh->GetLODInfo(InOverallMaxLODs));

	//��ȡ��ǰ��Ƥ�Ķ���
	TArray<FFinalSkinVertex> FinalVertices;
	InComponent->GetCPUSkinnedVertices(FinalVertices, InOverallMaxLODs);

	//��ȡ��ǰ������MeshRenderData
	FSkeletalMeshRenderData& SkeletalMeshRenderData = InComponent->MeshObject->GetSkeletalMeshRenderData();  

	//��ȡMeshLOD��Ӧ��renderData //�洢��ǰ��͹�������Ϣ�Լ�buffer
	FSkeletalMeshLODRenderData &LODData = SkeletalMeshRenderData.LODRenderData[InOverallMaxLODs];

	//�������е�λ�ı��������ҽ��п���
	for (int32 VerticIndex = 0;VerticIndex<FinalVertices.Num();VerticIndex++)
	{
		//��ӵ����ݽ�����һ������ת�����Ӿֲ�����תΪ�������꣨�ھ����У�
		OutRawMesh.VertexPositions.Add(InComponentToWorld.TransformPosition(FinalVertices[VerticIndex].Position));
	}

	//�ȴ�С����ȡ��Сֵ
	const uint32 NumTexCoords = FMath::Min(LODData.StaticVertexBuffers.StaticMeshVertexBuffer.GetNumTexCoords(), (uint32)MAX_MESH_TEXTURE_COORDS);
	const int32 NumSections = LODData.RenderSections.Num(); //��õ�ǰ��Ⱦ�ֶ�����

	FRawStaticIndexBuffer16or32Interface& IndexBuffer = *LODData.MultiSizeIndexContainer.GetIndexBuffer();

	//�Ի�ȡ����Buffer���б�������Ӧ���Section���б���
	for (int32 SectionIndex = 0;SectionIndex<NumSections;SectionIndex++)
	{
		//��ù�����Ⱦ�ֶ�
		const FSkelMeshRenderSection& SkelMeshSection = LODData.RenderSections[SectionIndex];

		//��鵱ǰ�ķֶεĲ����Ƿ�����ʾ�ģ������ڲ�������������صĻ᷵����
		if (InComponent->IsMaterialSectionShown(SkelMeshSection.MaterialIndex, InOverallMaxLODs))  //��ȡLOD��MaterialIndex
		{
			const int32 NumWedges = SkelMeshSection.NumTriangles * 3;  //3�����������һ��Wedge������׶��

			//������ǰ����׶��Ȼ���ȡ����������Ӧ������׶��
			for (int32 WedgeIndex = 0;WedgeIndex<NumWedges;WedgeIndex++)
			{
				const int32 VertexIndexForWedge = IndexBuffer.Get(SkelMeshSection.BaseIndex + WedgeIndex);
				OutRawMesh.WedgeIndices.Add(VertexIndexForWedge);  //��ȡ����Ӧ������׶ID��Ȼ�����ID��ӵ�����������

				//�����ȡ����Ƥ�Ķ��㣬ͨ��������ȡ��ǰ���ߵ�X��Z���������
				const FFinalSkinVertex& SkinnedVertex = FinalVertices[VertexIndexForWedge];

				//��ȡ��ǰ������Ƥ����������(�ֲ��ռ�ת��Ϊ����ռ�)
				//�����SkinnedVertex.TangentX.ToFVector()�������ľ����������꣬Ȼ��ֱ��תΪXYZ��Vector
				const FVector TangentX = InComponentToWorld.TransformVector(SkinnedVertex.TangentX.ToFVector());
				const FVector TangentZ = InComponentToWorld.TransformVector(SkinnedVertex.TangentZ.ToFVector());

				//��ȡZ����ľ������ֵ��Ҫ�õ�����W:������꣩
				const FVector4 UnpackedTangentZ = SkinnedVertex.TangentZ.ToFVector4();

				//ͨ������ X�����Z���� �Ĳ�ˣ��õ���ֱX��Z��Y������������ȡ��ǰY�ĳ���				
				const FVector TangentY = (TangentZ ^ TangentX).GetSafeNormal() * UnpackedTangentZ.W;
				//���㷽ʽ���� X = X / W �� Y = Y / W
				
				OutRawMesh.WedgeTangentX.Add(TangentX);
				OutRawMesh.WedgeTangentY.Add(TangentY);
				OutRawMesh.WedgeTangentZ.Add(TangentZ);

				// MAX_MESH_TEXTURE_COORDS = 8
				//����������UV�ı�������UV��skeletalMeshת��StaticMesh����
				for (uint32 TexCoordIndex = 0;TexCoordIndex<MAX_MESH_TEXTURE_COORDS;TexCoordIndex++)
				{
					//�����ǰ��UVֵ������С��UV Index
					if (TexCoordIndex >= NumTexCoords)
					{
						//���ֵ��Ļ������һ��Ĭ�Ͽռ䣬��������
						OutRawMesh.WedgeTexCoords[TexCoordIndex].AddDefaulted();
					}
					else
					{
						//��Ӷ�Ӧ��LODData��UV
						OutRawMesh.WedgeTexCoords[TexCoordIndex].Add
						(LODData.StaticVertexBuffers.StaticMeshVertexBuffer.GetVertexUV(VertexIndexForWedge, TexCoordIndex));

						//��Ӻ�����TrackerΪTrue
						OutRawMeshTracker.bValidTexCoords[TexCoordIndex] = true;
					}
				}

				//�жϵ�ǰ������ɫ�Ƿ��Ѿ���ʼ���������ʼ���ͽ������
				if (LODData.StaticVertexBuffers.ColorVertexBuffer.IsInitialized())
				{
					OutRawMesh.WedgeColors.Add(LODData.StaticVertexBuffers.ColorVertexBuffer.VertexColor(VertexIndexForWedge));
					OutRawMeshTracker.bValidColors = true;
				}
				else
				{
					//û�г�ʼ�����Զ����һ����ɫ
					OutRawMesh.WedgeColors.Add(FColor::White);
				}
			}

			//��ʼ�������
			int32 MaterialIndex = SkelMeshSection.MaterialIndex;
			//�жϵ�ǰIndex�Ĳ����Ƿ�����Ч��
			if (ScrLODInfo.LODMaterialMap.IsValidIndex(SectionIndex)&& ScrLODInfo.LODMaterialMap[SectionIndex]!=INDEX_NONE)
			{
				//���������Ч������ӳ���������(��Χ��0 - ����ģ�͵�����������)
				//ScrLODInfo.LODMaterialMap ������������в��ʵ�����
				//���Index������Χ�ˣ���ô�ͻᱻ�ü�
				MaterialIndex = FMath::Clamp<int32>(ScrLODInfo.LODMaterialMap[SectionIndex], 0, InComponent->SkeletalMesh->Materials.Num());

			}

			//����õ����ʺ�ʼ���б���Copy
			for (uint32 TriIndex = 0;TriIndex<SkelMeshSection.NumTriangles;TriIndex++)
			{
				OutRawMesh.FaceMaterialIndices.Add(MaterialIndex);
				OutRawMesh.FaceSmoothingMasks.Add(0);  //����0��ֱ�Ӻ������ֵ
			}

		}
	}

}


UStaticMesh* MeshUtils::SkeletalCompToStaticMesh(UWorld* World, USkeletalMeshComponent* SkeletalMeshComp)
{
	//������ʱMesh����
	UStaticMesh* TempStaticMesh = nullptr;


	//����һ��ԭʼ���ݵ����飨���Ǻ�ͼ����ص�һ�����ݣ��пտ��Կ�����
	FRawMesh TargetRawMesh;
	FMeshTracker MeshTracker;
	int32 OverallMaxLODs = 0;  //ֻ��Ҫ��һ����Ǹ�LOD��ģ��ת��Ϊ��ɫģ�ͼ���


	//��ʼ��һ����ʱλ��
	const FTransform& InRootTransform = FTransform::Identity; //Ĭ�ϵ�λTransform(W = 1)

	FMatrix WorldToRoot = InRootTransform.ToMatrixWithScale().Inverse();  //��õ�λ����
	//��ת�������Ҫ��������ô�ͳ��������漴�ɡ���Inverse)
	
	//����õ���ǰ���������ľ���
	FMatrix ComponentToWorld = SkeletalMeshComp->GetComponentTransform().ToMatrixWithScale() * WorldToRoot;

	
	if (IsValldSkeletalMeshComponent(SkeletalMeshComp))
	{
		//����ת������
		/** 
		1������������
		2��������Ҫ��ȡ��LOD = 0
		3�������Ӧ�����ת������������
		4����ȡ���ص�MeshTracker
		5����ȡ���ص�RawMesh
		*/
		SkeletalMeshToRawMeshes(SkeletalMeshComp, OverallMaxLODs, ComponentToWorld, MeshTracker, TargetRawMesh);
	}

	//�����Ч�Ķ�����ɫ����������
	uint32 MaxInUseTextureCoordiante = 0;

	//�жϵ�ǰ��ɫ�Ƿ���Ч
	if (!MeshTracker.bValidColors)
	{
		//�����Ч��ֱ�����
		TargetRawMesh.WedgeColors.Empty();
	}
	
	//������ǰ����������(uv)
	for (uint32 TexCoordIndex = 0;TexCoordIndex<MAX_MESH_TEXTURE_COORDS;TexCoordIndex++ )
	{
		if (!MeshTracker.bValidTexCoords[TexCoordIndex])
		{
			//Current TexCoord isn't Valid
			TargetRawMesh.WedgeTexCoords[TexCoordIndex].Empty();
		}
		else
		{
			//�����Ч�ͻ�ȡ�����ʹ�õ���ͼ���ꡣ
			MaxInUseTextureCoordiante = FMath::Max(MaxInUseTextureCoordiante, TexCoordIndex);
		}
	}


	//�жϵ�ǰRawMesh�Ƿ����������
	if (TargetRawMesh.IsValidOrFixable())
	{
		//��ʼID���ƣ�������һ��Mesh 
		FString MeshName = FGuid::NewGuid().ToString();

		//ʹ��RF_Transient ��Ϊ�˸���World�����ģ�Ͳ���Ҫ�������л������̣�ֻ������Ϸ�н���ʹ�á�
		TempStaticMesh = NewObject<UStaticMesh>(World, *MeshName, RF_Transient);  //����һ��Mesh

		TempStaticMesh->InitResources();  // ��ʼ��Mesh��Դ

		//���ɹ��յ�GUID
		TempStaticMesh->LightingGuid = FGuid::NewGuid();
		
		//��ȡ��ǰ�ƹ���ͼ��Ҳ����Ĭ�ϱȵ�ǰ��ģ������ID+1 ����UV�Ĺ������ꡣ��1-7��
		//MaxInUseTextureCoordiante = 0��Ĭ�Ͼ������屾��Ĳ���
		const uint32 LightMapIndex = FMath::Min(MaxInUseTextureCoordiante+1,(uint32)8 -1);


		//���������ȾΪ��̬ģ�͵�ģ��Դ��

		//���Ȼ�ȡ��̬ģ��Դ
		FStaticMeshSourceModel& SrcModel = TempStaticMesh->AddSourceModel();

		//�������¼��������еķ��֣����Ժ��Լ���
		SrcModel.BuildSettings.bRecomputeNormals = false;

		//����Ҳ�������
		SrcModel.BuildSettings.bRecomputeTangents = false;

		//�Ƴ��޷����ɵ�������
		SrcModel.BuildSettings.bRemoveDegenerates = true;

		// �ر���ʮ��λ�԰�λ�ľ��������д���(Precision = ����)
		SrcModel.BuildSettings.bUseHighPrecisionTangentBasis = false;

		// �Ƿ�Ҫ��ȫ���㾫�����洢UV������Ҫ��,GPU��������
		SrcModel.BuildSettings.bUseFullPrecisionUVs = false;

		// �Ƿ����ɵƹ���ͼ,��ģ�����ú���Զ��決һ��
		SrcModel.BuildSettings.bGenerateLightmapUVs = true;

		// �ƹ���ͼIDΪ0 
		SrcModel.BuildSettings.SrcLightmapIndex = 0;

		// Ŀ�����ͼ���� = �ƹ���ͼ�������������õ��Ǹ���
		SrcModel.BuildSettings.DstLightmapIndex = LightMapIndex;

		//��rawmesh������ӵ��ṹ��
		SrcModel.SaveRawMesh(TargetRawMesh);

		//������İ汾����Ϊ��һ�α���İ汾
		TempStaticMesh->ImportVersion = EImportStaticMeshVersion::LastVersion;

		//���ù�����ͼ���� = ��������
		TempStaticMesh->LightMapCoordinateIndex = LightMapIndex;


		//����һ������������Ψһ�ģ�
		TArray<int32> UniqueMaterialIndices;
		for (int32 MaterialIndex: TargetRawMesh.FaceMaterialIndices)  //�Ե�ǰ���ʽ��б���
		{
			UniqueMaterialIndices.AddUnique(MaterialIndex);
		}

		// �Բ��ʽ��б���
		for (int32 i = 0; i<UniqueMaterialIndices.Num() ;i++)
		{
			//���õ�ǰLOD��Ŀǰֻ����1��������Ϊ0�� ����кܶ�LOD�Ļ�����LOD���б�������
			// ��Բ��ʽ���������Ϣ
			//���ö�Ӧ��SectionInfo
			TempStaticMesh->GetSectionInfoMap().Set(0,i,FMeshSectionInfo(UniqueMaterialIndices[i]));
		}

		//��ȡ��Ӧ��ԭʼSection map�����棩,����ǰSection Map����ΪԭʼSection Map
		TempStaticMesh->GetOriginalSectionInfoMap().CopyFrom(TempStaticMesh->GetSectionInfoMap());

		//�Ե�ǰģ�ͽ��к決
		TempStaticMesh->Build(false);

	}

	return TempStaticMesh;
}
