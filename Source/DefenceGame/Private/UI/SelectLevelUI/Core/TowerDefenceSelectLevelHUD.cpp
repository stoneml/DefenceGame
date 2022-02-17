// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SelectLevelUI/Core/TowerDefenceSelectLevelHUD.h"
#include <UI/SelectLevelUI/UMG/UI_MainSelectLevel.h>
#include <UObject/ConstructorHelpers.h>

ATowerDefenceSelectLevelHUD::ATowerDefenceSelectLevelHUD()
{
	//���캯����ȡ��Ӧ��ͼ��UI
	static ConstructorHelpers::FClassFinder<UUI_MainSelectLevel> SelectMain_BPClass(TEXT("WidgetBlueprint'/Game/UI/Select/MainSelectLevel_BP.MainSelectLevel_BP_C'"));
	//UI���и�ֵ
	MainSelectLevelClass = SelectMain_BPClass.Class;

}

void ATowerDefenceSelectLevelHUD::BeginPlay()
{
	Super::BeginPlay();

	//��BeginPlay��ʱ��UI�������
	MainSelectLevel = CreateWidget<UUI_MainSelectLevel>(GetWorld(), MainSelectLevelClass);
	MainSelectLevel->AddToViewport();

}
