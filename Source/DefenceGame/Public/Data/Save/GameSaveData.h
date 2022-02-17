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

	//��ǰTowerID
	UPROPERTY(SaveGame)
	int32 TowerID;

	//��Ҫ�Ľ��
	UPROPERTY(SaveGame)
	int32 NeedGold;

	//׼���׶�����������
	UPROPERTY(SaveGame)
	int32 TowersPerpareBuildingNumber;

	//���Ѿ����������
	UPROPERTY(SaveGame)
	int32 TowersConstructionNumber;

	//��ǰ�������CD
	UPROPERTY(SaveGame)
	float MaxConstructionTowersCD;

	//��ǰ����������CD
	UPROPERTY(SaveGame)
	float CurrentConstrictionTowersCD;

	//��ΪICONָ��
	UPROPERTY(SaveGame)
	UTexture2D* Icon;

	//�Ƿ�����קͼ��
	UPROPERTY(SaveGame)
	bool bDragICO;

	//�Ƿ����cdˢ�µ���ͣ����
	UPROPERTY(SaveGame)
	bool bLockCD;

	//�Ƿ���ø�������Ϣ
	UPROPERTY(SaveGame)
	bool bCallUpdateTowerInfo;


public:

	FBuildingTower();

	//��ʼ��GameSave
	void InitSaveData();

	//��ȡ��ǰ������ʱ��İٷֱ�
	float GetTowerConstructionTimePercentage();

	//�жϵ�ǰ�����Ƿ���Ч
	bool IsValid();

	//���õ�ǰCDΪ���ֵ
	void ResetCD();


};




UCLASS()
class DEFENCEGAME_API UGameSaveData : public USaveGame
{
	GENERATED_BODY()

public:

	//����SaveGame��Ҫ���������
	UPROPERTY(SaveGame)
	TMap<FGuid,FCharacterData> CharacterDatas;


	UPROPERTY(SaveGame)
	TMap<FGuid,FBuildingTower> BuildingTowers;



};
