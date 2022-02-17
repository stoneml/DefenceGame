#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GameSaveSlotList.generated.h"

USTRUCT()
struct FSaveSlot
{

	GENERATED_USTRUCT_BODY()

public:
	FSaveSlot();

	//�洢�����ݺ�����
	UPROPERTY(SaveGame)
	FText DataText;

	//��Ӧ�浵��ID
	UPROPERTY(SaveGame)
	bool bSave;


};

USTRUCT()
struct FSaveSlotList
{
	GENERATED_USTRUCT_BODY()

public:

	FSaveSlotList();

	UPROPERTY(SaveGame)
	TMap<int32,FSaveSlot> Slots;

	//��Ӧĳ���ؿ�����ɽ���
	UPROPERTY(SaveGame)
	TMap<int32,float> ProgressOfCompletion;


	//��ȡ��ǰ�ܹ����б���Ĵ浵ID
	int32 GetSerialNumber();

	//ɾ����ǰ�浵
	bool RemoveAtGameData(int32 SlotNumber);

	//��Ӵ浵����
	bool AddGameData(int32 SlotNumber);


};



UCLASS()
class DEFENCEGAME_API UGameSaveSlotList : public USaveGame
{

	GENERATED_BODY()

public:

	//����һ����ǰSlotList
	UPROPERTY(SaveGame)
	FSaveSlotList CurrentSlotList;


};