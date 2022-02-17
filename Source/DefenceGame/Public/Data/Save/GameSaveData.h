// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "../Core/CharacterData.h"
#include "UObject/NoExportTypes.h"
#include "GameSaveData.generated.h"

/**
 * 
 */


USTRUCT(BlueprintType)
struct FBuildingTower
{
	GENERATED_USTRUCT_BODY()

public:

	//当前TowerID
	UPROPERTY(SaveGame)
	int32 TowerID;

	//需要的金币
	UPROPERTY(SaveGame)
	int32 NeedGold;

	//准备阶段塔建造数量
	UPROPERTY(SaveGame)
	int32 TowersPerpareBuildingNumber;

	//塔已经建造的数量
	UPROPERTY(SaveGame)
	int32 TowersConstructionNumber;

	//当前他最大建造CD
	UPROPERTY(SaveGame)
	float MaxConstructionTowersCD;

	//当前建造中塔的CD
	UPROPERTY(SaveGame)
	float CurrentConstrictionTowersCD;

	//作为ICON指针
	UPROPERTY(SaveGame)
	UTexture2D* Icon;

	//是否在拖拽图标
	UPROPERTY(SaveGame)
	bool bDragICO;

	//是否进行cd刷新的暂停锁定
	UPROPERTY(SaveGame)
	bool bLockCD;

	//是否调用更新塔信息
	UPROPERTY(SaveGame)
	bool bCallUpdateTowerInfo;


public:

	FBuildingTower();

	//初始化GameSave
	void InitSaveData();

	//获取当前塔建造时间的百分比
	float GetTowerConstructionTimePercentage();

	//判断当前数据是否有效
	bool IsValid();

	//重置当前CD为最大值
	void ResetCD();


};




UCLASS()
class DEFENCEGAME_API UGameSaveData : public USaveGame
{
	GENERATED_BODY()

public:

	//设置SaveGame需要保存的数据
	UPROPERTY(SaveGame)
	TMap<FGuid,FCharacterData> CharacterDatas;


	UPROPERTY(SaveGame)
	TMap<FGuid,FBuildingTower> BuildingTowers;



};
