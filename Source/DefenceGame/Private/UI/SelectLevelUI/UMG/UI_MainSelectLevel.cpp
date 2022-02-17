// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SelectLevelUI/UMG/UI_MainSelectLevel.h"
#include <Components/CanvasPanel.h>
#include <Components/PanelSlot.h>
#include <UI/SelectLevelUI/UMG/Button/UI_LevelButton.h>
#include <Components/Button.h>
#include <Kismet/GameplayStatics.h>

void UUI_MainSelectLevel::NativeConstruct()
{
	Super::NativeConstruct();

	//��ʼ��
	InitSelectLevelButton();

	//�󶨰���(����Buttonͷ�ļ�)
	ReturnMenuButton->OnReleased.AddDynamic(this, &UUI_MainSelectLevel::ReturnMenu);

}

void UUI_MainSelectLevel::InitSelectLevelButton()
{
	//ָ�뱣����ȷ��canvas����Ч��
	if (SelectMap)
	{
		//PanneSlot�Կռ�����Ű���ʽ���Ų���λ�ƣ���С���ŵȣ�
		//�����ȡ��CanvasPanel�ϵ�����slot
		TArray<UPanelSlot* >PanelSlotArray = SelectMap->GetSlots();

		//������Slot���б���
		for (UPanelSlot*PanelSlot : PanelSlotArray)
		{
			//�����������Slot��LevelButton
			if (UUI_LevelButton* LevelButtonArp = Cast<UUI_LevelButton>(PanelSlot->Content))
			{
				//����������Button���뵽������
				AllLevelButtons.Add(LevelButtonArp);
			}
		}
	}
}

void UUI_MainSelectLevel::ReturnMenu()
{
	//�������ؿ�
	UGameplayStatics::OpenLevel(GetWorld(), "HallMap");
}
