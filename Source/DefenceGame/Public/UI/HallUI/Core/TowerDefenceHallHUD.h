// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TowerDefenceHallHUD.generated.h"

/**
 * 
 */

class UUI_MainHall;

UCLASS()
class DEFENCEGAME_API ATowerDefenceHallHUD : public AHUD
{
	GENERATED_BODY()
	

public:
	ATowerDefenceHallHUD();


	virtual void BeginPlay() override;

protected:

	//MainHallClass是用来捕捉外部蓝图资源的
	//创建的UMG
	//TSubclassOf 就是可以在蓝图中进行内容填写，就类似开启了变量的Edit一样
	TSubclassOf<UUI_MainHall>MainHallClass;

	//创建一个主菜单的UMG
	UUI_MainHall* MainHall;


};
