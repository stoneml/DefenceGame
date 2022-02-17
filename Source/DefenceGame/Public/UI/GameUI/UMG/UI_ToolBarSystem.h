// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Core/UI_RuleOfTheWidget.h"
#include "UI_ToolBarSystem.generated.h"

/**
 * 
 */

class UTextBlock;
class UProgressBar;

UCLASS()
class DEFENCEGAME_API UUI_ToolBarSystem : public UUI_RuleOfTheWidget
{
	GENERATED_BODY()
	

private:
	//游戏金币数量
	UPROPERTY(meta = (BindWidget))
		UTextBlock* GameGold;
	//我方塔死亡数量
	UPROPERTY(meta = (BindWidget))
		UTextBlock* TowerDeathNumber;
	//游戏时间
	UPROPERTY(meta = (BindWidget))
		UTextBlock* GameCount;
	//击杀数量
	UPROPERTY(meta = (BindWidget))
		UTextBlock* KillSolider;

	//显示剩余敌人数量 (Surplus:剩余) （Quantity：数量)
	UPROPERTY(meta = (BindWidget))
		UTextBlock* GameLevelSurplusQuantity;

	//完成击杀进度条
	UPROPERTY(meta = (BindWidget))
		UProgressBar* GSQProgressBar;

public:

	virtual void NativeConstruct();


};
