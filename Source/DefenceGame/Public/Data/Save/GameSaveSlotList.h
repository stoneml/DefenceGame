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

	//存储的内容和日期
	UPROPERTY(SaveGame)
	FText DataText;

	//对应存档的ID
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

	//对应某个关卡的完成进度
	UPROPERTY(SaveGame)
	TMap<int32,float> ProgressOfCompletion;


	//获取当前能够进行保存的存档ID
	int32 GetSerialNumber();

	//删除当前存档
	bool RemoveAtGameData(int32 SlotNumber);

	//添加存档内容
	bool AddGameData(int32 SlotNumber);


};



UCLASS()
class DEFENCEGAME_API UGameSaveSlotList : public USaveGame
{

	GENERATED_BODY()

public:

	//创建一个当前SlotList
	UPROPERTY(SaveGame)
	FSaveSlotList CurrentSlotList;


};