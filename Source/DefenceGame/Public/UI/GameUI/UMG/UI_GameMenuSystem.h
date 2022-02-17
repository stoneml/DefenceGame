// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Core/UI_RuleOfTheWidget.h"
#include "UI_GameMenuSystem.generated.h"

/**
 * 
 */

class UButton;

UCLASS()
class DEFENCEGAME_API UUI_GameMenuSystem : public UUI_RuleOfTheWidget
{
	GENERATED_BODY()
	
private:

	//返回游戏按钮
	UPROPERTY(meta = (BindWidget))
		UButton* ReturnGameButton;

	//保存游戏按钮
	UPROPERTY(meta = (BindWidget))
		UButton* SaveGameButton;

	//游戏设置按钮
	UPROPERTY(meta = (BindWidget))
		UButton* GameSettingButton;

	//游戏退出按钮
	UPROPERTY(meta = (BindWidget))
		UButton* GameQuitButton;



public:

	//初始化UI
	virtual void NativeConstruct();


private:
	//按键对应的函数
	//因为绑定的是动态多播，所以需要添加UFUNCTION
	UFUNCTION()
		void ReturnGame();
	UFUNCTION()
		void SaveGame();
	UFUNCTION()
		void GameSetting();
	UFUNCTION()
		void GameQuit();



};
