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

	//初始化
	InitSelectLevelButton();

	//绑定按键(包含Button头文件)
	ReturnMenuButton->OnReleased.AddDynamic(this, &UUI_MainSelectLevel::ReturnMenu);

}

void UUI_MainSelectLevel::InitSelectLevelButton()
{
	//指针保护，确保canvas是有效的
	if (SelectMap)
	{
		//PanneSlot对空间进行排版样式的排布（位移，大小缩放等）
		//这里获取到CanvasPanel上的所有slot
		TArray<UPanelSlot* >PanelSlotArray = SelectMap->GetSlots();

		//对所有Slot进行遍历
		for (UPanelSlot*PanelSlot : PanelSlotArray)
		{
			//如果遍历到的Slot是LevelButton
			if (UUI_LevelButton* LevelButtonArp = Cast<UUI_LevelButton>(PanelSlot->Content))
			{
				//将遍历到的Button放入到数组中
				AllLevelButtons.Add(LevelButtonArp);
			}
		}
	}
}

void UUI_MainSelectLevel::ReturnMenu()
{
	//返回主关卡
	UGameplayStatics::OpenLevel(GetWorld(), "HallMap");
}
