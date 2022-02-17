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

	//��������������Ϣ(���������������Ǳ���Ҫ��ɵ�)
	UPROPERTY(meta = (BindWidget))
		UTextBlock* ConditionBase;

	//����A
	UPROPERTY(meta = (BindWidget))
		UTextBlock* ConditionA;

	//����B
	UPROPERTY(meta = (BindWidget))
		UTextBlock* ConditionB;

	//����ť
	UPROPERTY(meta = (BindWidget))
		UButton* ConditionButton;

public:

	virtual void NativeConstruct();

	//�����󶨵ĺ���
	UFUNCTION()
		void Condition();

};
