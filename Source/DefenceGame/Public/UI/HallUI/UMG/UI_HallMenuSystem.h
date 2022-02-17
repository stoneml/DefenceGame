// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Core/UI_RuleOfTheWidget.h"
#include <Components/Button.h>
#include "UI_HallMenuSystem.generated.h"

/**
 * 
 */

//菜单UI

//声明按钮类
class UButton;


UCLASS()
class DEFENCEGAME_API UUI_HallMenuSystem : public UUI_RuleOfTheWidget
{
	GENERATED_BODY()
	


protected:

	//开始游戏按钮
	UPROPERTY(meta = (BindWidget))
		UButton* GameStartButton;

	//添加秘境按钮
	UPROPERTY(meta = (BindWidget))
		UButton* SecretTerritoryButton;

	//用于载入游戏或者储存游戏的
	UPROPERTY(meta = (BindWidget))
		UButton* HistoryButton;

	//游戏设置按钮
	UPROPERTY(meta = (BindWidget))
		UButton* GameSettingsButton;

	//打开视频按钮
	UPROPERTY(meta = (BindWidget))
		UButton* TutorialWebsiteButton;

	//浏览器按钮（打开网站）
	UPROPERTY(meta = (BindWidget))
		UButton* BrowerButton;

	//特别内容也就是DLC
	UPROPERTY(meta = (BindWidget))
		UButton* SpecialContentButton;

	//退出游戏
	UPROPERTY(meta = (BindWidget))
		UButton* QuitGameButton;


public:

	//初始化按钮 = BrginPlay
	virtual void NativeConstruct();


	//创建对应按键的绑定接口，绑定父类的函数
	void BindGameStart(FOnButtonReleasedEvent ReleaseEvent);
	void BindSecretTerritory(FOnButtonReleasedEvent ReleaseEvent);
	void BindHistory(FOnButtonReleasedEvent ReleaseEvent);
	void BindGameSettings(FOnButtonReleasedEvent ReleaseEvent);
	void BindTutorialWebsite(FOnButtonReleasedEvent ReleaseEvent);
	void BindBrower(FOnButtonReleasedEvent ReleaseEvent);
	void BindSpecialContent(FOnButtonReleasedEvent ReleaseEvent);
	void BindQuitGame(FOnButtonReleasedEvent ReleaseEvent);



};
