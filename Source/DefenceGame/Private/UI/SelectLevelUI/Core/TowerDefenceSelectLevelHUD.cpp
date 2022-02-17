// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SelectLevelUI/Core/TowerDefenceSelectLevelHUD.h"
#include <UI/SelectLevelUI/UMG/UI_MainSelectLevel.h>
#include <UObject/ConstructorHelpers.h>

ATowerDefenceSelectLevelHUD::ATowerDefenceSelectLevelHUD()
{
	//构造函数获取对应蓝图的UI
	static ConstructorHelpers::FClassFinder<UUI_MainSelectLevel> SelectMain_BPClass(TEXT("WidgetBlueprint'/Game/UI/Select/MainSelectLevel_BP.MainSelectLevel_BP_C'"));
	//UI进行赋值
	MainSelectLevelClass = SelectMain_BPClass.Class;

}

void ATowerDefenceSelectLevelHUD::BeginPlay()
{
	Super::BeginPlay();

	//在BeginPlay的时候将UI进行添加
	MainSelectLevel = CreateWidget<UUI_MainSelectLevel>(GetWorld(), MainSelectLevelClass);
	MainSelectLevel->AddToViewport();

}
