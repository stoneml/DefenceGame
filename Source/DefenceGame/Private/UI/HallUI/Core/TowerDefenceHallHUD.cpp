// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HallUI/Core/TowerDefenceHallHUD.h"
#include <UObject/ConstructorHelpers.h>
#include <UI/HallUI/UMG/UI_MainHall.h>

ATowerDefenceHallHUD::ATowerDefenceHallHUD()
{
	//获取蓝图资源
	static ConstructorHelpers::FClassFinder<UUI_MainHall>MainHall_BPClass(TEXT("WidgetBlueprint'/Game/UI/Hall/HallMain_BP.HallMain_BP_C'"));
	//将蓝图BP赋值给C++类
	MainHallClass = MainHall_BPClass.Class;
}

void ATowerDefenceHallHUD::BeginPlay()
{
	Super::BeginPlay();
	
	//类似蓝图功能的CreateWidget
	MainHall = CreateWidget<UUI_MainHall>(GetWorld(), MainHallClass);
	MainHall->AddToViewport();
}
