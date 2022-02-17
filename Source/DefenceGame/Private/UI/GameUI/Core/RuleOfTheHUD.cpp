// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameUI/Core/RuleOfTheHUD.h"
#include <UObject/ConstructorHelpers.h>
#include <UI/GameUI/UMG/UI_MainScreen.h>

ARuleOfTheHUD::ARuleOfTheHUD()
{
	static ConstructorHelpers::FClassFinder<UUI_MainScreen> MainScreen_BPClass(TEXT("WidgetBlueprint'/Game/UI/Game/MainScreen_BP.MainScreen_BP_C'"));
	MainScreenClass = MainScreen_BPClass.Class;
}

void ARuleOfTheHUD::BeginPlay()
{
	
	Super::BeginPlay();

	ShowMainUI();
/*
	//创建主要UI并且进行添加到屏幕
	MainScreen = CreateWidget<UUI_MainScreen>(GetWorld(), MainScreenClass);
	MainScreen->AddToViewport();*/

}

void ARuleOfTheHUD::ShowMainUI()
{
	//创建主要UI并且进行添加到屏幕
	MainScreen = CreateWidget<UUI_MainScreen>(GetWorld(), MainScreenClass);
	MainScreen->AddToViewport();
}
