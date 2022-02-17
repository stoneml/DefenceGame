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

	//和做资产配置一样

	//UniformGridPanel用来进行摆放UI按钮
	UPROPERTY(meta = (BindWidget))
		UUniformGridPanel* SlotArrayInventory;

	//使用一个数组将所有拿到的Slot放在一起
	TArray<UUI_InventorySlot*> InventroySlotArray;


	//获取一个InvetorySlot的Class
	//EditDefaultsOnly 只能在类默认面板的Details中显示
	UPROPERTY(EditDefaultsOnly, Category = UI)
		TSubclassOf<UUI_InventorySlot> InventorySlotClass;

/*
	//塔的数据表格
	UPROPERTY()
		UDataTable* AITowerCharacterData;

	//怪物的数据表格
	UPROPERTY()
		UDataTable* AIMonsterCharacterData;*/

	TArray<FCharacterData*>ReturnData;

	//TowerDoll模型的材质
	UPROPERTY(EditDefaultsOnly,Category = UI)
	UMaterialInterface* DollMaterial;

protected:

	virtual void NativeConstruct();

	//布局InventorySlot的一个函数(column：列，row：行)
	void LayoutInventorySlot(int32 ColumnNumber, int32 RowNumber);

	//生成塔的函数
	void SpawnTowerDollPressed();
	void SpawnTowerDollReleased();

	//通过GUID获取对应的UI信息
	FBuildingTower& GetBuildingTower();

	
};
