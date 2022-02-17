// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameUI/UMG/Skill/UI_SkillSlot.h"
#include <Components/Button.h>

void UUI_SkillSlot::NativeConstruct()
{
	Super::NativeConstruct();

	//µã»÷°´Å¥
	ClickButton->OnReleased.AddDynamic(this, &UUI_SkillSlot::OnReleasedWidget);

}

void UUI_SkillSlot::OnReleasedWidget()
{

}
