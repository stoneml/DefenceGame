// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Core/UI_RuleOfTheWidget.h"
#include "UI_MainSelectLevel.generated.h"

/**
 * 
 */

class UUI_LevelButton;
class UButton;
class UCanvasPanel;

UCLASS()
class DEFENCEGAME_API UUI_MainSelectLevel : public UUI_RuleOfTheWidget
{
	GENERATED_BODY()

public:

	//UI��ʼ������
	virtual void NativeConstruct();

protected:

	//��ʼ��ѡ���LevelButton
	void InitSelectLevelButton();

	//��ӷ��ز˵��ĺ���
	UFUNCTION()
	void ReturnMenu();

private:

	//����һ���������˵���Button
	UPROPERTY(meta = (BindWidget))
		UButton* ReturnMenuButton;
	
	//ͨ��canvas��壬��ȡ��������������LevelButton
	UPROPERTY(meta = (BindWidget))
		UCanvasPanel* SelectMap;

	//�������йؿ��İ�ť����
	TArray<UUI_LevelButton*> AllLevelButtons;
	
};
