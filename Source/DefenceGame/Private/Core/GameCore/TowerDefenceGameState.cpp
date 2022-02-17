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


//����һ����̬���ݣ�����Ҫ���ؿ����ݵ�ʱ��ʹ��
FCharacterData CharacterDataNULL;
FBuildingTower BuildingTowerNULL;

ATowerDefenceGameState::ATowerDefenceGameState()
{
	//����Tick
	PrimaryActorTick.bCanEverTick = true;

	//��������ȡ��ͼ���
	static ConstructorHelpers::FObjectFinder<UDataTable>MyTable_AITowerObj(TEXT("DataTable'/Game/GameData/TowerData.TowerData'"));
	static ConstructorHelpers::FObjectFinder<UDataTable>MyTable_AIMonsterObj(TEXT("/Game/GameData/MonsterData"));
	AITowerCharacterData = MyTable_AITowerObj.Object;
	AIMonsterCharacterData = MyTable_AIMonsterObj.Object;


	//������ǰ�����б�����GUID
	for (int32 i = 0; i < 21; i++)
	{
		GetSaveData()->BuildingTowers.Add(FGuid::NewGuid(), FBuildingTower());
		
		//AddBulidingTower(FGuid::NewGuid(), FBuildingTower());  //ʹ�õ�ǰ�Լ�д����Ӻ�����
	}

}

ATowers* ATowerDefenceGameState::SpawnTower(int32 CharacterID, int32 CharacterLevel, const FVector& Location, const FRotator& Rotation)
{
	//������
	return SpawnCharacter<ATowers>(CharacterID, CharacterLevel, AITowerCharacterData, Location, Rotation);
}

AMonster* ATowerDefenceGameState::SpawnMonster(int32 CharacterID, int32 CharacterLevel, const FVector& Location, const FRotator& Rotation)
{
	//���ɹ���
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
		//ͨ��Row����ȡ��ӦDataTable����
		TArray<FCharacterData*> Datas;
		InCharacterData->GetAllRows(TEXT("Character Data"), Datas);

		//ʹ��һ��Lambda��ʽ����ȡ��ӦID��������Ϣ
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
		};  //Lambda������Ҫ�÷ֺŽ�β

		if (FCharacterData* CharacterData = GetCharacterData(CharacterID))
		{
			//��ȡ��Ӧ����
			UClass* NewClass = GetCharacterData(CharacterID)->CharacterBlueprintKey.LoadSynchronous();  //ͬ����ȡ����

			if (GetWorld() && NewClass)
			{
				if (ARuleOfTheCharacter* RuleOfCharacter = GetWorld()->SpawnActor<ARuleOfTheCharacter>(NewClass, Location, Rotation))
				{
					/*//����ǰҪ������Character����һ����Ӧ��GUID
					RuleOfCharacter->GUID = FGuid::NewGuid();*/
					//����һ���µ�data��Ȼ��ֵ
					//RuleOfCharacter->CurrentGUID = FGuid::NewGuid();

					UKismetSystemLibrary::PrintString(this, RuleOfCharacter->CurrentGUID.ToString(),true,true,FLinearColor::Blue,5.f);

					CharacterData->UpdateHealth();
/*					//��鵱ǰUI����
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
	//��ʹ�õ�һ��AStaticMeshActor(UE�Լ��ģ�
	//�����������ģ��

	AActor* OutActor = nullptr;
	//���ȴ�datatable��ȡ����
	TArray<const FCharacterData*> TmpDatas;
	GetTowerCharacterDataFromTable(TmpDatas);

	for (const auto& tmp : TmpDatas)
	{
		if (tmp->CharacterID == InID)
		{
			//��ȡ֮ǰ�����TSubClassOf����
			UClass* NewClass = tmp->CharacterBlueprintKey.LoadSynchronous();

			if (GetWorld() && NewClass)
			{
				if (ARuleOfTheCharacter* RuleOfActor = GetWorld()->SpawnActor<ARuleOfTheCharacter>(NewClass,FVector::ZeroVector,FRotator::ZeroRotator))
				{
					//��Ҫʹ�õ�AStaticMeshActor��
					if (AStaticMeshActor* MeshActor = GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator))
					{
						if (UStaticMesh* TargetMesh = RuleOfActor->GetDollMesh())
						{
							//������û�ȡ����RuleOfCharacter��mesh��MeshActor
							MeshActor->SetMobility(EComponentMobility::Movable);
							MeshActor->GetStaticMeshComponent()->SetStaticMesh(TargetMesh);
							MeshActor->GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
							OutActor = MeshActor;
							RuleOfActor->Destroy();  //ɾ����ʱ������RuleActor

						}
						else
						{
							//�����ȡ���ɹ����Ͱ����ɵ�������actor��������
							MeshActor->Destroy();
							RuleOfActor->Destroy();
						}
					}
					else
					{
						//MeshActor���ɲ��ɹ��ͽ�ruleOfActor��������
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
	//��Ӷ�Ӧ�Ľ�ɫ����
	return GetSaveData()->CharacterDatas.Add(ID, Data);
}

bool ATowerDefenceGameState::RemoveCharacterData(const FGuid& ID)
{
	//���ɾ����Ч�᷵��0��ɾ���ɹ��᷵�ض�Ӧ��ID
	return (bool)GetSaveData()->CharacterDatas.Remove(ID);
}

FCharacterData& ATowerDefenceGameState::GetCharacterData(const FGuid& ID)
{
	//ͨ���������еĽ�ɫ����������ָ��������
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

	//���ش�����Ϣ
	//SD_print_r(Error,"The current [%s] is invalid", *ID.ToString());
	return CharacterDataNULL;
}

UGameSaveData* ATowerDefenceGameState::GetSaveData()
{
	if (!CurrentSaveData)
	{
		//��ȡ��ǰ��GameSaveData
		CurrentSaveData = Cast<UGameSaveData>(UGameplayStatics::CreateSaveGameObject(UGameSaveData::StaticClass()));
	}
	return CurrentSaveData;
}

UGameSaveSlotList* ATowerDefenceGameState::GetGameSaveSlotList()
{
	if (!CurrentSaveList)
	{
		//���Ƚ���Slot�Ķ�ȡ
		CurrentSaveList = Cast<UGameSaveSlotList>(UGameplayStatics::LoadGameFromSlot(FString::Printf(TEXT("SlotList")), 0));

		//�����ȡʧ�ܵĻ��ʹ���һ��
		if (!CurrentSaveList)
		{
			CurrentSaveList = Cast<UGameSaveSlotList>(UGameplayStatics::CreateSaveGameObject(UGameSaveSlotList::StaticClass()));
		}
	}
	return CurrentSaveList;
}

bool ATowerDefenceGameState::SaveGameData(int32 SaveNumber)
{
	//�ж��Ƿ���Ч�������Ч�ͽ��б���
	if (CurrentSaveData&&CurrentSaveList)
	{
		//���浱ǰ��Slot
		CurrentSaveList->CurrentSlotList.AddGameData(SaveNumber);

		//ֻ������slot�ʹ浵�����б���ɹ��˲ŷ�����
		return UGameplayStatics::SaveGameToSlot(CurrentSaveList, FString::Printf(TEXT("SlotList")), 0)
			&& UGameplayStatics::SaveGameToSlot(CurrentSaveData, FString::Printf(TEXT("SaveSlot_%i"), SaveNumber), 0);
	}
	return false;
}

bool ATowerDefenceGameState::LoadSaveGameData(int32 SaveNumber)
{
	//��ȡ��ǰ�Ĵ洢����
	CurrentSaveData = Cast<UGameSaveData>(UGameplayStatics::LoadGameFromSlot(FString::Printf(TEXT("SaveSlot_%i"), SaveNumber), 0));

	//�����Ϊ�վͷ�����
	return CurrentSaveData != nullptr;
}



FBuildingTower& ATowerDefenceGameState::GetBuildingTower(const FGuid& ID)
{
	//��ȡ�����е�BuildingTower��Ϣ
	if (GetSaveData()->BuildingTowers.Contains(ID))
	{
		return GetSaveData()->BuildingTowers[ID];
	}

	//SD_print_r(Error, "The current [%s] is invaild", *ID.ToString());
	return BuildingTowerNULL;
}

TArray<const FGuid*> ATowerDefenceGameState::GetBuildingTowerID()
{
	//����һ����ʱ��ID
	TArray<const FGuid*>TempID;
	//ѭ��������ǰ���е�ID��Ȼ�����һ�����ݿ�����
	for (auto& Tmp : GetSaveData()->BuildingTowers)
	{
		TempID.Add(&Tmp.Key);
	}

	return TempID;
}


const FBuildingTower& ATowerDefenceGameState::AddBulidingTower(const FGuid& ID, const FBuildingTower& Data)
{
	//��Ӷ�Ӧ��TowerData
	return GetSaveData()->BuildingTowers.Add(ID, Data);
}


bool ATowerDefenceGameState::GetTowerCharacterDataFromTable(TArray<const FCharacterData*> &Datas)
{
	if (!TowerCacheDatas.Num())
	{
		AITowerCharacterData->GetAllRows(TEXT("Character Data"), TowerCacheDatas);
	}

	//��ȡ�����ݺ󣬽����ݴ���
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
	//�����const FCharacterData�ǵ�һ�θ�ֵ��ʱ�����Կ���ʹ�����
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

	//������ȡ�������飬����ID����
	for (const auto & Tmp : TempDatas)
	{
		if (Tmp->CharacterID == InID)
		{
			return *Tmp;
		}
	}

	//���û���������ͷ��ؿ�����
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

	FBuildingTower& ASlot = GetBuildingTower(A);  //A��Ŀ��Slot
	FBuildingTower& BSlot = GetBuildingTower(B);

	if (ASlot.IsValid())  //����
	{
		FBuildingTower Temp = ASlot;
		ASlot = BSlot;
		BSlot = Temp;
	}
	else //�ƶ�
	{
		ASlot = BSlot;
		BSlot.InitSaveData();
	}

	return true;
}

