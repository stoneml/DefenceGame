// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Core/UI_Slot.h"
#include "UI_SkillSlot.generated.h"

/**
 * 
 */

class UImage;
class UTextBlock;
class UButton;

UCLASS()
class DEFENCEGAME_API UUI_SkillSlot : public UUI_Slot
{
	GENERATED_BODY()
	

private:

	//技能图标
	UPROPERTY(meta = (BindWidget))
		UImage* SkillIcon;

	//技能CD蒙版图片
	UPROPERTY(meta = (BindWidget))
		UImage* SkillIconCD;

	//技能数量
	UPROPERTY(meta = (BindWidget))
		UTextBlock* SkillNumber;

	//按键数字
	UPROPERTY(meta = (BindWidget))
		UTextBlock* KeyValueNumber;

	//技能CD，文字方式显示
	UPROPERTY(meta = (BindWidget))
		UTextBlock* SkilCDValue;

	//按键点击（不仅可以按键盘还可以点击鼠标使用）
	UPROPERTY(meta = (BindWidget))
		UButton* ClickButton;

public:

	virtual void NativeConstruct();

	//鼠标点击对应函数
	UFUNCTION()
		void OnReleasedWidget();

};
