// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Data/Core/CharacterData.h"
#include "Data/Save/GameSaveData.h"
#include "../DefenceGameType.h"
#include "TowerDefenceGameState.generated.h"


/**
 * 
 */
class ARuleOfTheCharacter;
class UDataTable;
class ATowers;
class AMonster;
class UGameSaveData;
class UGameSaveSlotList;
//struct ECharacterType;

 //ͨ��extern������֪ͨ�ⲿ���������
  extern FCharacterData CharacterDataNULL;
  extern FBuildingTower BuildingTowerNULL;

UCLASS()
class DEFENCEGAME_API ATowerDefenceGameState : public AGameState
{
	GENERATED_BODY()
	

public:

	ATowerDefenceGameState();


	//��¶���ɽӿ��ṩ�ⲿ����
	UFUNCTION(BlueprintCallable,Category = "Spawn")
	ATowers* SpawnTower(int32 CharacterID, int32 CharacterLevel, const FVector& Location, const FRotator& Rotation);

	UFUNCTION(BlueprintCallable,Category = "Spawn")
	AMonster* SpawnMonster(int32 CharacterID, int32 CharacterLevel, const FVector& Location, const FRotator& Rotation);

	//���ɴ�������ģ��
	AActor* SpawnTowersDoll(int32 InID);

protected:

	//�������ɽ�ɫ��
	//����һ��ָ��
	ARuleOfTheCharacter* SpawnCharacter(int32 CharacterID,
		int32 CharacterLevel,
		UDataTable* InCharacterData, 
		const FVector& Location, 
		const FRotator& Rotation);


	//����һ��ģ��������Actor��Spawn
	template<class T>
	T* SpawnCharacter(int32 CharacterID, int32 CharacterLevel, UDataTable* InCharacterData, const FVector& Location, const FRotator& Rotation)
	{
		return Cast<T>(SpawnCharacter(CharacterID, CharacterLevel, InCharacterData, Location, Rotation));
	}




public:

	//������ɾ�Ĳ�Ľӿ�
	const FCharacterData& AddFCharacterData(const FGuid& ID, const FCharacterData& Data);
	
	bool RemoveCharacterData(const FGuid& ID);

	FCharacterData& GetCharacterData(const FGuid& ID);

	//��ȡ��ǰ��SaveGameData
	UGameSaveData* GetSaveData();

	//��ȡ��ǰSlotList
	UGameSaveSlotList* GetGameSaveSlotList();

	//�����ɫ����
	bool SaveGameData(int32 SaveNumber);

	//��ȡ��������
	bool LoadSaveGameData(int32 SaveNumber);


	//BuildingTower

	//��ȡBuildingTower
	FBuildingTower& GetBuildingTower(const FGuid& ID);

	//��ȡ��ǰBuildingTowerID
	TArray<const FGuid*>GetBuildingTowerID();


	//���BuildingTower
	const FBuildingTower& AddBulidingTower(const FGuid& ID, const FBuildingTower& Data);

	//�����ݱ��л�ȡ��ɫ����
	bool GetTowerCharacterDataFromTable(TArray<const FCharacterData*> &Datas);
	bool GetMonsterCharacterDataFromTable(TArray<const FCharacterData*> &Datas);

	//���TipUI��������
	//ͨ��ID��ȡ��Ӧ��Data����
	const FCharacterData GetCharacterDataByID(int32 InID, ECharacterType Type = ECharacterType::TOWER);

	//TArray<FCharacterData*>GetCurrnetCharacterDataFromTable();

	UFUNCTION(BlueprintCallable)
	void PrintInfo();


	





	//����slot���л�����
	
	bool RequestInvetorySlotSwap(const FGuid& A, const FGuid& B);


private:

	//�����ID��Ϊʹ��UE�Լ���UniqueID

/*
	//����һ����������
	UPROPERTY()
	TMap<uint32,FCharacterData> CharacterDatas;*/

	//����һ�����������������֮ǰ������Data
	UPROPERTY()
	UGameSaveData* CurrentSaveData;

	//��ǰSavelist
	UPROPERTY()
	UGameSaveSlotList* CurrentSaveList;


	//�������ݱ��
	UPROPERTY()
	UDataTable* AITowerCharacterData;

	//��������ݱ��
	UPROPERTY()
	UDataTable* AIMonsterCharacterData;



	//��ɫ����
	TArray<FGuid>CharacterIDs;



	//���ȫ�ֵĶ�ӦTower��Data
	TArray<FCharacterData*> TowerCacheDatas;

	TArray<FCharacterData*> MonsterCacheDatas;

};
