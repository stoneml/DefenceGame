#include "Data/Save/GameSaveSlotList.h"


#define LOCTEXT_NAMESPACE "SaveSlot"


FSaveSlot::FSaveSlot()
	:DataText(LOCTEXT("SaveSlot","Save Slot Hello World~~")),
	bSave(false)
{

}



FSaveSlotList::FSaveSlotList()
{
	//需要有20个slot
	for (int32 i =0;i<20;i++)
	{
		Slots.Add(i, FSaveSlot());
	}
	//只有5个关卡，每个每个关卡初始进度为0
	for (int32 i = 1;i<6;i++)
	{
		ProgressOfCompletion.Add(i, 0.0f);
	}
}

int32 FSaveSlotList::GetSerialNumber()
{
	//进行存档检测遍历
	for (auto &Tmp : Slots)
	{
		if (!Tmp.Value.bSave)
		{
			//获取到对应可使用的存档插槽
			return Tmp.Key;
		}
	}

	//获取失败
	return INDEX_NONE;
}

bool FSaveSlotList::RemoveAtGameData(int32 SlotNumber)
{
	if (Slots.Contains(SlotNumber))
	{
		//存档移除成功
		Slots[SlotNumber].bSave = false;
		return true;
	}
	return false;
}

bool FSaveSlotList::AddGameData(int32 SlotNumber)
{
	if (Slots.Contains(SlotNumber))
	{
		//如果包含对应Id的话，就进行保存
		Slots[SlotNumber].bSave = true;
		return true;
	}
	return false;
}



#undef LOCTEXT_NAMESPACE