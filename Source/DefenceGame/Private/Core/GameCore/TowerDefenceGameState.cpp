// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/GameCore/TowerDefenceGameState.h"
#include "Data/Core/CharacterData.h"
#include "../DefenceGameMacro.h"
#include "GameFramework/Actor.h"
#include "Character/Core/RuleOfTheCharacter.h"
#include "Engine/Engine.h"
#include "Engine/DataTable.h"
#include "Character/CharacterCore/Towers.h"
#include "Character/CharacterCore/Monster.h"
#include "Kismet/GameplayStatics.h"
#include "Data/Save/GameSaveData.h"
#include "Data/Save/GameSaveSlotList.h"
#include "../DefenceGameType.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/World.h"


//创建一个静态数据，在需要返回空数据的时候使用
FCharacterData CharacterDataNULL;
FBuildingTower BuildingTowerNULL;

ATowerDefenceGameState::ATowerDefenceGameState()
{
	//开启Tick
	PrimaryActorTick.bCanEverTick = true;

	//这里来获取蓝图表格。
	static ConstructorHelpers::FObjectFinder<UDataTable>MyTable_AITowerObj(TEXT("DataTable'/Game/GameData/TowerData.TowerData'"));
	static ConstructorHelpers::FObjectFinder<UDataTable>MyTable_AIMonsterObj(TEXT("/Game/GameData/MonsterData"));
	AITowerCharacterData = MyTable_AITowerObj.Object;
	AIMonsterCharacterData = MyTable_AIMonsterObj.Object;


	//创建当前所有列表按键的GUID
	for (int32 i = 0; i < 21; i++)
	{
		GetSaveData()->BuildingTowers.Add(FGuid::NewGuid(), FBuildingTower());
		
		//AddBulidingTower(FGuid::NewGuid(), FBuildingTower());  //使用当前自己写的添加函数。
	}

}

ATowers* ATowerDefenceGameState::SpawnTower(int32 CharacterID, int32 CharacterLevel, const FVector& Location, const FRotator& Rotation)
{
	//生成塔
	return SpawnCharacter<ATowers>(CharacterID, CharacterLevel, AITowerCharacterData, Location, Rotation);
}

AMonster* ATowerDefenceGameState::SpawnMonster(int32 CharacterID, int32 CharacterLevel, const FVector& Location, const FRotator& Rotation)
{
	//生成怪物
	return SpawnCharacter<AMonster>(CharacterID, CharacterLevel, AIMonsterCharacterData, Location, Rotation);
}

ARuleOfTheCharacter* ATowerDefenceGameState::SpawnCharacter(int32 CharacterID, 
	int32 CharacterLevel,
	UDataTable* InCharacterData,
	const FVector& Location, 
	const FRotator& Rotation)
{

	if (InCharacterData)
	{
		//通过Row来获取对应DataTable内容
		TArray<FCharacterData*> Datas;
		InCharacterData->GetAllRows(TEXT("Character Data"), Datas);

		//使用一个Lambda公式来获取对应ID的数据信息
		auto GetCharacterData = [&](int32 ID)->FCharacterData*
		{
			for (auto& tmp : Datas)
			{
				if (tmp->CharacterID == ID)
				{
					return tmp;
				}
			}
			return nullptr;
		};  //Lambda后面需要用分号结尾

		if (FCharacterData* CharacterData = GetCharacterData(CharacterID))
		{
			//读取对应的类
			UClass* NewClass = GetCharacterData(CharacterID)->CharacterBlueprintKey.LoadSynchronous();  //同步读取数据

			if (GetWorld() && NewClass)
			{
				if (ARuleOfTheCharacter* RuleOfCharacter = GetWorld()->SpawnActor<ARuleOfTheCharacter>(NewClass, Location, Rotation))
				{
					/*//给当前要创建的Character创建一个对应的GUID
					RuleOfCharacter->GUID = FGuid::NewGuid();*/
					//创建一个新的data，然后赋值
					//RuleOfCharacter->CurrentGUID = FGuid::NewGuid();

					UKismetSystemLibrary::PrintString(this, RuleOfCharacter->CurrentGUID.ToString(),true,true,FLinearColor::Blue,5.f);

					CharacterData->UpdateHealth();
/*					//检查当前UI数组
					CharacterIDs.Add(RuleOfCharacter->CurrentGUID);
					UKismetSystemLibrary::PrintString(this, FString::FromInt(CharacterIDs.Num()));*/
					AddFCharacterData(RuleOfCharacter->CurrentGUID, *CharacterData);
					return RuleOfCharacter;
				}
			}
		}
	}
	
	return nullptr;
}



AActor* ATowerDefenceGameState::SpawnTowersDoll(int32 InID)
{
	//会使用到一个AStaticMeshActor(UE自己的）
	//用来生成替代模型

	AActor* OutActor = nullptr;
	//首先从datatable获取数据
	TArray<const FCharacterData*> TmpDatas;
	GetTowerCharacterDataFromTable(TmpDatas);

	for (const auto& tmp : TmpDatas)
	{
		if (tmp->CharacterID == InID)
		{
			//获取之前保存的TSubClassOf的类
			UClass* NewClass = tmp->CharacterBlueprintKey.LoadSynchronous();

			if (GetWorld() && NewClass)
			{
				if (ARuleOfTheCharacter* RuleOfActor = GetWorld()->SpawnActor<ARuleOfTheCharacter>(NewClass,FVector::ZeroVector,FRotator::ZeroRotator))
				{
					//需要使用到AStaticMeshActor。
					if (AStaticMeshActor* MeshActor = GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator))
					{
						if (UStaticMesh* TargetMesh = RuleOfActor->GetDollMesh())
						{
							//最后设置获取到的RuleOfCharacter的mesh给MeshActor
							MeshActor->SetMobility(EComponentMobility::Movable);
							MeshActor->GetStaticMeshComponent()->SetStaticMesh(TargetMesh);
							MeshActor->GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
							OutActor = MeshActor;
							RuleOfActor->Destroy();  //删除临时创建的RuleActor

						}
						else
						{
							//如果获取不成功，就把生成的那两个actor进行销毁
							MeshActor->Destroy();
							RuleOfActor->Destroy();
						}
					}
					else
					{
						//MeshActor生成不成功就将ruleOfActor进行销毁
						RuleOfActor->Destroy();
					}
				}

				break;				
			}	
		}
	}

	return OutActor;

}

const FCharacterData& ATowerDefenceGameState::AddFCharacterData(const FGuid& ID, const FCharacterData& Data)
{
	//添加对应的角色数据
	return GetSaveData()->CharacterDatas.Add(ID, Data);
}

bool ATowerDefenceGameState::RemoveCharacterData(const FGuid& ID)
{
	//如果删除无效会返回0，删除成功会返回对应的ID
	return (bool)GetSaveData()->CharacterDatas.Remove(ID);
}

FCharacterData& ATowerDefenceGameState::GetCharacterData(const FGuid& ID)
{
	//通过遍历所有的角色数据来返回指定的数据
	if (GetSaveData()->CharacterDatas.Contains(ID))
	{
		return GetSaveData()->CharacterDatas[ID];
	}

/*
	for (auto& tmp: CharacterDatas)
	{
		if (tmp.Key == Hash)
		{
			return tmp.Value;
		}
	}*/

	//返回错误信息
	//SD_print_r(Error,"The current [%s] is invalid", *ID.ToString());
	return CharacterDataNULL;
}

UGameSaveData* ATowerDefenceGameState::GetSaveData()
{
	if (!CurrentSaveData)
	{
		//获取当前的GameSaveData
		CurrentSaveData = Cast<UGameSaveData>(UGameplayStatics::CreateSaveGameObject(UGameSaveData::StaticClass()));
	}
	return CurrentSaveData;
}

UGameSaveSlotList* ATowerDefenceGameState::GetGameSaveSlotList()
{
	if (!CurrentSaveList)
	{
		//首先进行Slot的读取
		CurrentSaveList = Cast<UGameSaveSlotList>(UGameplayStatics::LoadGameFromSlot(FString::Printf(TEXT("SlotList")), 0));

		//如果读取失败的话就创建一个
		if (!CurrentSaveList)
		{
			CurrentSaveList = Cast<UGameSaveSlotList>(UGameplayStatics::CreateSaveGameObject(UGameSaveSlotList::StaticClass()));
		}
	}
	return CurrentSaveList;
}

bool ATowerDefenceGameState::SaveGameData(int32 SaveNumber)
{
	//判断是否有效，如果有效就进行保存
	if (CurrentSaveData&&CurrentSaveList)
	{
		//保存当前的Slot
		CurrentSaveList->CurrentSlotList.AddGameData(SaveNumber);

		//只有满足slot和存档都进行保存成功了才返回真
		return UGameplayStatics::SaveGameToSlot(CurrentSaveList, FString::Printf(TEXT("SlotList")), 0)
			&& UGameplayStatics::SaveGameToSlot(CurrentSaveData, FString::Printf(TEXT("SaveSlot_%i"), SaveNumber), 0);
	}
	return false;
}

bool ATowerDefenceGameState::LoadSaveGameData(int32 SaveNumber)
{
	//读取当前的存储数据
	CurrentSaveData = Cast<UGameSaveData>(UGameplayStatics::LoadGameFromSlot(FString::Printf(TEXT("SaveSlot_%i"), SaveNumber), 0));

	//如果不为空就返回真
	return CurrentSaveData != nullptr;
}



FBuildingTower& ATowerDefenceGameState::GetBuildingTower(const FGuid& ID)
{
	//获取数组中的BuildingTower信息
	if (GetSaveData()->BuildingTowers.Contains(ID))
	{
		return GetSaveData()->BuildingTowers[ID];
	}

	//SD_print_r(Error, "The current [%s] is invaild", *ID.ToString());
	return BuildingTowerNULL;
}

TArray<const FGuid*> ATowerDefenceGameState::GetBuildingTowerID()
{
	//创建一个临时的ID
	TArray<const FGuid*>TempID;
	//循环遍历当前已有的ID，然后进行一个传递拷贝。
	for (auto& Tmp : GetSaveData()->BuildingTowers)
	{
		TempID.Add(&Tmp.Key);
	}

	return TempID;
}


const FBuildingTower& ATowerDefenceGameState::AddBulidingTower(const FGuid& ID, const FBuildingTower& Data)
{
	//添加对应的TowerData
	return GetSaveData()->BuildingTowers.Add(ID, Data);
}


bool ATowerDefenceGameState::GetTowerCharacterDataFromTable(TArray<const FCharacterData*> &Datas)
{
	if (!TowerCacheDatas.Num())
	{
		AITowerCharacterData->GetAllRows(TEXT("Character Data"), TowerCacheDatas);
	}

	//获取到数据后，将数据传入
	for (const auto &Tmp : TowerCacheDatas)
	{
		Datas.Add(Tmp);
	}

	//AITowerCharacterData->GetAllRows(TEXT("Character Data"), Datas);
	return Datas.Num() > 0;
}


bool ATowerDefenceGameState::GetMonsterCharacterDataFromTable(TArray<const FCharacterData*>& Datas)
{
	if (!MonsterCacheDatas.Num())
	{
		AITowerCharacterData->GetAllRows(TEXT("Character Data"), MonsterCacheDatas);
	}

	for (const auto &Tmp: MonsterCacheDatas)
	{
		Datas.Add(Tmp);
	}

	return Datas.Num()>0;
}

const FCharacterData ATowerDefenceGameState::GetCharacterDataByID(int32 InID, ECharacterType Type /*= ECharacterType::TOWER*/)
{
	//这里的const FCharacterData是第一次赋值的时，所以可以使用这个
	//TArray<const FCharacterData* > TempDatas;
	TArray<const FCharacterData* > TempDatas;
	switch (Type)
	{
	case ECharacterType::TOWER:

		GetTowerCharacterDataFromTable(TempDatas);
		break;
	case ECharacterType::MONSTER:
		GetMonsterCharacterDataFromTable(TempDatas);
		break;
	}

	//遍历获取到的数组，进行ID搜索
	for (const auto & Tmp : TempDatas)
	{
		if (Tmp->CharacterID == InID)
		{
			return *Tmp;
		}
	}

	//如果没有搜索到就返回空数据
	return CharacterDataNULL;
}

/*
TArray<FCharacterData*> ATowerDefenceGameState::GetCurrnetCharacterDataFromTable()
{	
	TArray<FCharacterData*>tmp;
	AITowerCharacterData->GetAllRows(TEXT("Character Data"), tmp);
	return tmp;
}*/


void ATowerDefenceGameState::PrintInfo()
{
	if (GetSaveData())
	{
		for (auto& tmp : GetSaveData()->CharacterDatas)
		{
			UKismetSystemLibrary::PrintString(this, (tmp.Key).ToString());
		}
	}
	TArray<const FCharacterData*> TmpData;
	GetTowerCharacterDataFromTable(TmpData);
	UKismetSystemLibrary::PrintString(this, FString::FromInt(TmpData.Num()));
}

bool ATowerDefenceGameState::RequestInvetorySlotSwap(const FGuid& A, const FGuid& B)
{

	FBuildingTower& ASlot = GetBuildingTower(A);  //A是目标Slot
	FBuildingTower& BSlot = GetBuildingTower(B);

	if (ASlot.IsValid())  //交换
	{
		FBuildingTower Temp = ASlot;
		ASlot = BSlot;
		BSlot = Temp;
	}
	else //移动
	{
		ASlot = BSlot;
		BSlot.InitSaveData();
	}

	return true;
}

