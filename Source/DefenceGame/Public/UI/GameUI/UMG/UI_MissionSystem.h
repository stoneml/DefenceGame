// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Core/UI_RuleOfTheWidget.h"
#include "UI_MissionSystem.generated.h"

/**
 * 
 */


class UTextBlock;
class UButton;

UCLASS()
class DEFENCEGAME_API UUI_MissionSystem : public UUI_RuleOfTheWidget
{
	GENERATED_BODY()

private:

	//基础任务文字信息(基础条件（任务）是必须要完成的)
	UPROPERTY(meta = (BindWidget))
		UTextBlock* ConditionBase;

	//任务A
	UPROPERTY(meta = (BindWidget))
		UTextBlock* ConditionA;

	//任务B
	UPROPERTY(meta = (BindWidget))
		UTextBlock* ConditionB;

	//任务按钮
	UPROPERTY(meta = (BindWidget))
		UButton* ConditionButton;

public:

	virtual void NativeConstruct();

	//按键绑定的函数
	UFUNCTION()
		void Condition();

};
