// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameUI/UMG/UI_PlayerSkillSystem.h"
#include <GameFramework/InputSettings.h>
#include <GameFramework/PlayerInput.h>

void UUI_PlayerSkillSystem::NativeConstruct()
{
	Super::NativeConstruct();


	//对应按键映射
	//映射用到了一个lambda表达式
	auto KeyMapping = GetDefault<UInputSettings>()->GetActionMappings().FindByPredicate([&](FInputActionKeyMapping& EntryUI) { return (EntryUI.ActionName == "FreezeSkill"); });
	
}
