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

	//��������ȡ��ͼ���
	/*static ConstructorHelpers::FObjectFinder<UDataTable>MyTable_AITowerObj(TEXT("DataTable'/Game/GameData/TowerData.TowerData'"));
	static ConstructorHelpers::FObjectFinder<UDataTable>MyTable_AIMonsterObj(TEXT("/Game/GameData/MonsterData"));
	AITowerCharacterData = MyTable_AITowerObj.Object;
	AIMonsterCharacterData = MyTable_AIMonsterObj.Object;*/


	//���� 3��7��
	LayoutInventorySlot(3,7);
	
	//��PlayerController�е�֪ͨ�¼�
	GetPlayerController()->EventMouseMiddlePressed.BindUObject(this, &UUI_Inventory::SpawnTowerDollPressed);
	GetPlayerController()->EventMouseMiddleReleased.BindUObject(this, &UUI_Inventory::SpawnTowerDollReleased);


}

void UUI_Inventory::LayoutInventorySlot(int32 ColumnNumber, int32 RowNumber)
{

	if (InventorySlotClass)
	{
		//������Ʒ��   ������˵��һ��ʼ���ǵ�0�У�1,2,3������1�У�1,2,3����
		//����ѭ��
		for (int32 MyRow = 0; MyRow < RowNumber; MyRow++)
		{
			//�����������ܳ����������
			for (int32 MyColumn = 0; MyColumn< ColumnNumber;MyColumn++)
			{
				//ѭ��������Ȼ�󴴽�SlotUI
				UUI_InventorySlot* SlotWidget = CreateWidget<UUI_InventorySlot>(GetWorld(), InventorySlotClass);
				if (SlotWidget)
				{
					//��Ҫ�����ǵ�UMG��ӽ�ȥ
					//������ӵ�Panel֮��ͻ᷵��һ��Slot
					UUniformGridSlot* GridSlot = SlotArrayInventory->AddChildToUniformGrid(SlotWidget);
					if (GridSlot)
					{
						GridSlot->SetRow(MyRow);		//������
						GridSlot->SetColumn(MyColumn);	//������
						GridSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);	//ˮƽ���
						GridSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);	//��ֱ���
					}
				}
				//������ɺ󣬽�Slot�ŵ�Slot�����н��б���
				InventroySlotArray.Add(SlotWidget);
			}
		}
	}

	//Slot����Ҫȥ��ȡ�Ѿ������Ľ�ɫ��GUID
	//������Գ���һ����������GameState��дһ������GUID�Ľӿڣ�Ȼ�������������ʱ��ֱ�����һ��GUID��

	//ѭ�����������е�Slot֮�����ID��ȡ
	const TArray<const FGuid*> IDArr = GetGameState()->GetBuildingTowerID();
	if (IDArr.Num() > 0)
	{	//ѭ������С���ݺ���
		UKismetSystemLibrary::PrintString(this, FString::FromInt(IDArr.Num()));
		for (int32 i = 0; i < ColumnNumber * RowNumber; i++)
		{
			//������Ҫ���ַ
			InventroySlotArray[i]->CurrentGUID = *IDArr[i];
			UKismetSystemLibrary::PrintString(this, *(*IDArr[i]).ToString());
		}
	}

	//���õ�ǰ����Ҫ�����ݸ���Ӧ��Slot

	//TArray<FCharacterData*> Datas = GetGameState()->GetCurrnetCharacterDataFromTable();

	TArray<const FCharacterData*> Datas;
	if (GetGameState()->GetTowerCharacterDataFromTable(Datas))
	{
		for (int32 i = 0; i < Datas.Num(); i++)
		{
			InventroySlotArray[i]->GetBuildingTower().TowerID = Datas[i]->CharacterID;
			InventroySlotArray[i]->GetBuildingTower().NeedGold = Datas[i]->Gold;
			InventroySlotArray[i]->GetBuildingTower().MaxConstructionTowersCD = Datas[i]->ConstructionTime;
			//�����Textureʹ�õ���TAssetPtr��������Ҫʹ�ü���ͬ������������
			InventroySlotArray[i]->GetBuildingTower().Icon = Datas[i]->ICon.LoadSynchronous();

			//����������ɺ����UI����
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
		//��ǰ������������������1��ʱ��ִ��
		if (GetBuildingTower().TowersConstructionNumber>0)
		{
			int32 TmpTowerID = GetBuildingTower().TowerID;
			//���õ�ǰ��ȡ����Actor��TowerDoll�ϡ�
			
			if (AStaticMeshActor* Temp = Cast<AStaticMeshActor>(GetGameState()->SpawnTowersDoll(TmpTowerID)))
			{

				for (int32 i = 0; i< Temp->GetStaticMeshComponent()->GetNumMaterials();i++)
				{
					Temp->GetStaticMeshComponent()->SetMaterial(i, DollMaterial);
				}

				//���ò�����ɺ��������
				TowerDoll = Temp;
			}
			
		}
	}
}

void UUI_Inventory::SpawnTowerDollReleased()
{

	if (GetBuildingTower().IsValid())
	{
		//���������һ����ɫ��ģ�ͣ�����ʾ�������������ʲôλ��
		if (TowerDoll)
		{

			//�ͷŵ�ʱ�����ģ��
			if (GetBuildingTower().TowersConstructionNumber>=1)
			{
				if (ARuleOfTheCharacter* NewTower = GetGameState()->SpawnTower(GetBuildingTower().TowerID,1,TowerDoll->GetActorLocation(),TowerDoll->GetActorRotation()))
				{
					GetBuildingTower().TowersConstructionNumber--;
				}
			}

			//����ȫ��Doll
			TowerDoll->Destroy();
			TowerDoll = nullptr;

		}
	}

	bLockGUID = false;
	//�ͷŵ�ʱ���ÿյ�ǰTowerICOGuid
	TowerICOGuid = FGuid();  //����ᴴ��һ��000000�ı���
}


FBuildingTower& UUI_Inventory::GetBuildingTower()
{
	return GetGameState()->GetBuildingTower(TowerICOGuid);
}



