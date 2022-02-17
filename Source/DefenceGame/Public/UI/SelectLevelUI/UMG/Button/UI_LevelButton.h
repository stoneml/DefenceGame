// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Core/UI_RuleOfTheWidget.h"
#include "UI_LevelButton.generated.h"

/**
 * 
 */
UCLASS()
class DEFENCEGAME_API UUI_LevelButton : public UUI_RuleOfTheWidget
{
	GENERATED_BODY()

	//��Button����Ӵ���

public:

	//��ʼ��
	virtual void NativeConstruct();

	//ѡ��ؿ�
	//���button��ʱ�����ѡ��ؿ�
	UFUNCTION()
	void SelectLevel();

private:

	UPROPERTY(meta = (BindWidget))
		class UBorder* LevelBorder;

	//��ͼ�е�Image��ΪProgressbar
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* LevelProBar;

	UPROPERTY(meta = (BindWidget))
		class UButton* NextLevelButton;
	
	
};
