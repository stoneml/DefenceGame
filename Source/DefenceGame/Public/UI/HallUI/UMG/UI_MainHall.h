// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Core/UI_RuleOfTheWidget.h"
#include <Components/Button.h>
#include "UI_MainHall.generated.h"

/**
 * 
 */
UCLASS()
class DEFENCEGAME_API UUI_MainHall : public UUI_RuleOfTheWidget
{
	GENERATED_BODY()
	

public:

	//初始化UI
	virtual void NativeConstruct();

	//创建对应Button功能的函数
//然后将函数绑定到UButton上
//因为函数是需要通过动态多播去添加，所以需要添加UFunction
	UFUNCTION()
		void GameStart();

	UFUNCTION()
		void SecretTerritory();

	UFUNCTION()
		void Histroy();

	UFUNCTION()
		void GameSettings();

	UFUNCTION()
		void TutorialsWebsite();

	UFUNCTION()
		void Brower();

	UFUNCTION()
		void SpecialContent();

	UFUNCTION()
		void QuitGame();


protected:

	//绑定一个菜单组件
	UPROPERTY(meta = (BindWidget))
		class UUI_HallMenuSystem* HallMenuSystem;

	//绑定UI中的MainBorder
	UPROPERTY(meta = (BindWidget))
		class UBorder* MainBorder;

	//绑定UI中的BoxList
	UPROPERTY(meta = (BindWidget))
		class USizeBox* BoxList;

	//添加档案（存档）系统、游戏设置系统、教学系统的类
	UPROPERTY(EditDefaultsOnly, Category = UI)
		TSubclassOf<class UUI_ArchivesSystem> AcrchivesSystemClass;
	UPROPERTY(EditDefaultsOnly, Category = UI)
		TSubclassOf<class UUI_GameSettingsSystem> GameSettingsSystemClass;
	UPROPERTY(EditDefaultsOnly, Category = UI)
		TSubclassOf<class UUI_TutorialsWebsite> TutorialsSystemClass;


};
