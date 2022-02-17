// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameUI/UMG/Inventory/UI_Inventory.h"
#include <Blueprint/UserWidget.h>
#include <UI/GameUI/UMG/Inventory/UI_InventorySlot.h>
#include <Components/UniformGridSlot.h>
#include <Components/UniformGridPanel.h>
#include "Data/Core/CharacterData.h"
#include "UI/Core/UI_RuleOfTheWidget.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/DataTable.h"
#include "UObject/ConstructorHelpers.h"
#include "UI/Core/UI_Datas.h"
#include "Engine/StaticMeshActor.h"
#include "Character/Core/RuleOfTheCharacter.h"


void UUI_Inventory::NativeConstruct()
{
	Super::NativeConstruct();

	//这里来获取蓝图表格。
	/*static ConstructorHelpers::FObjectFinder<UDataTable>MyTable_AITowerObj(TEXT("DataTable'/Game/GameData/TowerData.TowerData'"));
	static ConstructorHelpers::FObjectFinder<UDataTable>MyTable_AIMonsterObj(TEXT("/Game/GameData/MonsterData"));
	AITowerCharacterData = MyTable_AITowerObj.Object;
	AIMonsterCharacterData = MyTable_AIMonsterObj.Object;*/


	//测试 3列7行
	LayoutInventorySlot(3,7);
	
	//绑定PlayerController中的通知事件
	GetPlayerController()->EventMouseMiddlePressed.BindUObject(this, &UUI_Inventory::SpawnTowerDollPressed);
	GetPlayerController()->EventMouseMiddleReleased.BindUObject(this, &UUI_Inventory::SpawnTowerDollReleased);


}

void UUI_Inventory::LayoutInventorySlot(int32 ColumnNumber, int32 RowNumber)
{

	if (InventorySlotClass)
	{
		//排序物品栏   （简单来说，一开始就是第0行，1,2,3个，第1行，1,2,3个）
		//行数循环
		for (int32 MyRow = 0; MyRow < RowNumber; MyRow++)
		{
			//这里列数不能超过最高列数
			for (int32 MyColumn = 0; MyColumn< ColumnNumber;MyColumn++)
			{
				//循环遍历，然后创建SlotUI
				UUI_InventorySlot* SlotWidget = CreateWidget<UUI_InventorySlot>(GetWorld(), InventorySlotClass);
				if (SlotWidget)
				{
					//需要将我们的UMG添加进去
					//当他添加到Panel之后就会返回一个Slot
					UUniformGridSlot* GridSlot = SlotArrayInventory->AddChildToUniformGrid(SlotWidget);
					if (GridSlot)
					{
						GridSlot->SetRow(MyRow);		//设置行
						GridSlot->SetColumn(MyColumn);	//设置列
						GridSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);	//水平填充
						GridSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);	//垂直填充
					}
				}
				//设置完成后，将Slot放到Slot数组中进行保存
				InventroySlotArray.Add(SlotWidget);
			}
		}
	}

	//Slot不需要去获取已经创建的角色的GUID
	//这里可以尝试一个方法，在GameState中写一个创建GUID的接口，然后在生成这里的时候，直接添加一个GUID。

	//循环创建好所有的Slot之后进行ID获取
	const TArray<const FGuid*> IDArr = GetGameState()->GetBuildingTowerID();
	if (IDArr.Num() > 0)
	{	//循环次数小于纵和排
		UKismetSystemLibrary::PrintString(this, FString::FromInt(IDArr.Num()));
		for (int32 i = 0; i < ColumnNumber * RowNumber; i++)
		{
			//这里需要解地址
			InventroySlotArray[i]->CurrentGUID = *IDArr[i];
			UKismetSystemLibrary::PrintString(this, *(*IDArr[i]).ToString());
		}
	}

	//设置当前所需要的数据给对应的Slot

	//TArray<FCharacterData*> Datas = GetGameState()->GetCurrnetCharacterDataFromTable();

	TArray<const FCharacterData*> Datas;
	if (GetGameState()->GetTowerCharacterDataFromTable(Datas))
	{
		for (int32 i = 0; i < Datas.Num(); i++)
		{
			InventroySlotArray[i]->GetBuildingTower().TowerID = Datas[i]->CharacterID;
			InventroySlotArray[i]->GetBuildingTower().NeedGold = Datas[i]->Gold;
			InventroySlotArray[i]->GetBuildingTower().MaxConstructionTowersCD = Datas[i]->ConstructionTime;
			//这里的Texture使用的是TAssetPtr，所以需要使用加载同步来进行引用
			InventroySlotArray[i]->GetBuildingTower().Icon = Datas[i]->ICon.LoadSynchronous();

			//设置数据完成后进行UI更新
			InventroySlotArray[i]->UpdateUI();
		}
	}

}

void UUI_Inventory::SpawnTowerDollPressed()
{
	UKismetSystemLibrary::PrintString(this, "Clicked");

	if (GetBuildingTower().IsValid())
	{
		bLockGUID = true;
		//当前建造的塔完成数量大于1的时候执行
		if (GetBuildingTower().TowersConstructionNumber>0)
		{
			int32 TmpTowerID = GetBuildingTower().TowerID;
			//设置当前获取到的Actor到TowerDoll上。
			
			if (AStaticMeshActor* Temp = Cast<AStaticMeshActor>(GetGameState()->SpawnTowersDoll(TmpTowerID)))
			{

				for (int32 i = 0; i< Temp->GetStaticMeshComponent()->GetNumMaterials();i++)
				{
					Temp->GetStaticMeshComponent()->SetMaterial(i, DollMaterial);
				}

				//设置材质完成后进行设置
				TowerDoll = Temp;
			}
			
		}
	}
}

void UUI_Inventory::SpawnTowerDollReleased()
{

	if (GetBuildingTower().IsValid())
	{
		//这里会生成一个绿色的模型，来提示玩家塔会生成在什么位置
		if (TowerDoll)
		{

			//释放的时候放置模型
			if (GetBuildingTower().TowersConstructionNumber>=1)
			{
				if (ARuleOfTheCharacter* NewTower = GetGameState()->SpawnTower(GetBuildingTower().TowerID,1,TowerDoll->GetActorLocation(),TowerDoll->GetActorRotation()))
				{
					GetBuildingTower().TowersConstructionNumber--;
				}
			}

			//重置全局Doll
			TowerDoll->Destroy();
			TowerDoll = nullptr;

		}
	}

	bLockGUID = false;
	//释放的时候置空当前TowerICOGuid
	TowerICOGuid = FGuid();  //这里会创建一个000000的变量
}


FBuildingTower& UUI_Inventory::GetBuildingTower()
{
	return GetGameState()->GetBuildingTower(TowerICOGuid);
}



