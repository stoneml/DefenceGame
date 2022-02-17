// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Core/UI_Slot.h"
#include "Data/Save/GameSaveData.h"
#include "UI_Inventory.generated.h"

/**
 * 
 */

class UUniformGridPanel;
class UUI_InventorySlot;
class UMaterialInterface;

UCLASS()
class DEFENCEGAME_API UUI_Inventory : public UUI_Slot
{
	GENERATED_BODY()


private:

	//�����ʲ�����һ��

	//UniformGridPanel�������аڷ�UI��ť
	UPROPERTY(meta = (BindWidget))
		UUniformGridPanel* SlotArrayInventory;

	//ʹ��һ�����齫�����õ���Slot����һ��
	TArray<UUI_InventorySlot*> InventroySlotArray;


	//��ȡһ��InvetorySlot��Class
	//EditDefaultsOnly ֻ������Ĭ������Details����ʾ
	UPROPERTY(EditDefaultsOnly, Category = UI)
		TSubclassOf<UUI_InventorySlot> InventorySlotClass;

/*
	//�������ݱ��
	UPROPERTY()
		UDataTable* AITowerCharacterData;

	//��������ݱ��
	UPROPERTY()
		UDataTable* AIMonsterCharacterData;*/

	TArray<FCharacterData*>ReturnData;

	//TowerDollģ�͵Ĳ���
	UPROPERTY(EditDefaultsOnly,Category = UI)
	UMaterialInterface* DollMaterial;

protected:

	virtual void NativeConstruct();

	//����InventorySlot��һ������(column���У�row����)
	void LayoutInventorySlot(int32 ColumnNumber, int32 RowNumber);

	//�������ĺ���
	void SpawnTowerDollPressed();
	void SpawnTowerDollReleased();

	//ͨ��GUID��ȡ��Ӧ��UI��Ϣ
	FBuildingTower& GetBuildingTower();

	
};
