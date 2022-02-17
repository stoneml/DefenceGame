#include "Data/Save/GameSaveSlotList.h"


#define LOCTEXT_NAMESPACE "SaveSlot"


FSaveSlot::FSaveSlot()
	:DataText(LOCTEXT("SaveSlot","Save Slot Hello World~~")),
	bSave(false)
{

}



FSaveSlotList::FSaveSlotList()
{
	//��Ҫ��20��slot
	for (int32 i =0;i<20;i++)
	{
		Slots.Add(i, FSaveSlot());
	}
	//ֻ��5���ؿ���ÿ��ÿ���ؿ���ʼ����Ϊ0
	for (int32 i = 1;i<6;i++)
	{
		ProgressOfCompletion.Add(i, 0.0f);
	}
}

int32 FSaveSlotList::GetSerialNumber()
{
	//���д浵������
	for (auto &Tmp : Slots)
	{
		if (!Tmp.Value.bSave)
		{
			//��ȡ����Ӧ��ʹ�õĴ浵���
			return Tmp.Key;
		}
	}

	//��ȡʧ��
	return INDEX_NONE;
}

bool FSaveSlotList::RemoveAtGameData(int32 SlotNumber)
{
	if (Slots.Contains(SlotNumber))
	{
		//�浵�Ƴ��ɹ�
		Slots[SlotNumber].bSave = false;
		return true;
	}
	return false;
}

bool FSaveSlotList::AddGameData(int32 SlotNumber)
{
	if (Slots.Contains(SlotNumber))
	{
		//���������ӦId�Ļ����ͽ��б���
		Slots[SlotNumber].bSave = true;
		return true;
	}
	return false;
}



#undef LOCTEXT_NAMESPACE