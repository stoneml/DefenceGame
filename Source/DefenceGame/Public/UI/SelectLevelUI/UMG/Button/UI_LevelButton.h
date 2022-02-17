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

	//在Button中添加代码

public:

	//初始化
	virtual void NativeConstruct();

	//选择关卡
	//点击button的时候可以选择关卡
	UFUNCTION()
	void SelectLevel();

private:

	UPROPERTY(meta = (BindWidget))
		class UBorder* LevelBorder;

	//蓝图中的Image改为Progressbar
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* LevelProBar;

	UPROPERTY(meta = (BindWidget))
		class UButton* NextLevelButton;
	
	
};
