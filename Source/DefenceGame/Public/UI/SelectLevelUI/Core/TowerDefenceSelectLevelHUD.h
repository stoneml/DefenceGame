// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TowerDefenceSelectLevelHUD.generated.h"

/**
 * 
 */

class UUI_MainSelectLevel;

UCLASS()
class DEFENCEGAME_API ATowerDefenceSelectLevelHUD : public AHUD
{
	GENERATED_BODY()


public:
	//添加HUD中的东西

	ATowerDefenceSelectLevelHUD();

	virtual void BeginPlay() override;


private:

	//获取对应的Actor进行绑定
	//这里是获取到这个UI的类
	TSubclassOf<UUI_MainSelectLevel>MainSelectLevelClass;

	//这里通过获取到UI的类然后进行UI赋值
	UUI_MainSelectLevel* MainSelectLevel;

};
