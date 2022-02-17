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

 //通过extern来进行通知外部有这个变量
  extern FCharacterData CharacterDataNULL;
  extern FBuildingTower BuildingTowerNULL;

UCLASS()
class DEFENCEGAME_API ATowerDefenceGameState : public AGameState
{
	GENERATED_BODY()
	

public:

	ATowerDefenceGameState();


	//暴露生成接口提供外部调用
	UFUNCTION(BlueprintCallable,Category = "Spawn")
	ATowers* SpawnTower(int32 CharacterID, int32 CharacterLevel, const FVector& Location, const FRotator& Rotation);

	UFUNCTION(BlueprintCallable,Category = "Spawn")
	AMonster* SpawnMonster(int32 CharacterID, int32 CharacterLevel, const FVector& Location, const FRotator& Rotation);

	//生成创建塔的模型
	AActor* SpawnTowersDoll(int32 InID);

protected:

	//创建生成角色。
	//返回一个指针
	ARuleOfTheCharacter* SpawnCharacter(int32 CharacterID,
		int32 CharacterLevel,
		UDataTable* InCharacterData, 
		const FVector& Location, 
		const FRotator& Rotation);


	//创建一个模板来进行Actor的Spawn
	template<class T>
	T* SpawnCharacter(int32 CharacterID, int32 CharacterLevel, UDataTable* InCharacterData, const FVector& Location, const FRotator& Rotation)
	{
		return Cast<T>(SpawnCharacter(CharacterID, CharacterLevel, InCharacterData, Location, Rotation));
	}




public:

	//创建增删改查的接口
	const FCharacterData& AddFCharacterData(const FGuid& ID, const FCharacterData& Data);
	
	bool RemoveCharacterData(const FGuid& ID);

	FCharacterData& GetCharacterData(const FGuid& ID);

	//获取当前的SaveGameData
	UGameSaveData* GetSaveData();

	//获取当前SlotList
	UGameSaveSlotList* GetGameSaveSlotList();

	//保存角色数据
	bool SaveGameData(int32 SaveNumber);

	//读取保存数据
	bool LoadSaveGameData(int32 SaveNumber);


	//BuildingTower

	//获取BuildingTower
	FBuildingTower& GetBuildingTower(const FGuid& ID);

	//获取当前BuildingTowerID
	TArray<const FGuid*>GetBuildingTowerID();


	//添加BuildingTower
	const FBuildingTower& AddBulidingTower(const FGuid& ID, const FBuildingTower& Data);

	//从数据表中获取角色数据
	bool GetTowerCharacterDataFromTable(TArray<const FCharacterData*> &Datas);
	bool GetMonsterCharacterDataFromTable(TArray<const FCharacterData*> &Datas);

	//针对TipUI增加内容
	//通过ID获取对应的Data参数
	const FCharacterData GetCharacterDataByID(int32 InID, ECharacterType Type = ECharacterType::TOWER);

	//TArray<FCharacterData*>GetCurrnetCharacterDataFromTable();

	UFUNCTION(BlueprintCallable)
	void PrintInfo();


	





	//进行slot的切换操作
	
	bool RequestInvetorySlotSwap(const FGuid& A, const FGuid& B);


private:

	//这里的ID改为使用UE自己的UniqueID

/*
	//创建一个数据数组
	UPROPERTY()
	TMap<uint32,FCharacterData> CharacterDatas;*/

	//创建一个保存数据用来替代之前的数据Data
	UPROPERTY()
	UGameSaveData* CurrentSaveData;

	//当前Savelist
	UPROPERTY()
	UGameSaveSlotList* CurrentSaveList;


	//塔的数据表格
	UPROPERTY()
	UDataTable* AITowerCharacterData;

	//怪物的数据表格
	UPROPERTY()
	UDataTable* AIMonsterCharacterData;



	//角色数组
	TArray<FGuid>CharacterIDs;



	//添加全局的对应Tower的Data
	TArray<FCharacterData*> TowerCacheDatas;

	TArray<FCharacterData*> MonsterCacheDatas;

};
