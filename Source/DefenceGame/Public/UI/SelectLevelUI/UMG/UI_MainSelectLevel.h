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

	//UI初始化函数
	virtual void NativeConstruct();

protected:

	//初始化选择的LevelButton
	void InitSelectLevelButton();

	//添加返回菜单的函数
	UFUNCTION()
	void ReturnMenu();

private:

	//创建一个返回主菜单的Button
	UPROPERTY(meta = (BindWidget))
		UButton* ReturnMenuButton;
	
	//通过canvas面板，获取到所有面板里面的LevelButton
	UPROPERTY(meta = (BindWidget))
		UCanvasPanel* SelectMap;

	//创建所有关卡的按钮数组
	TArray<UUI_LevelButton*> AllLevelButtons;
	
};
