// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HallUI/Core/TowerDefenceHallHUD.h"
#include <UObject/ConstructorHelpers.h>
#include <UI/HallUI/UMG/UI_MainHall.h>

ATowerDefenceHallHUD::ATowerDefenceHallHUD()
{
	//��ȡ��ͼ��Դ
	static ConstructorHelpers::FClassFinder<UUI_MainHall>MainHall_BPClass(TEXT("WidgetBlueprint'/Game/UI/Hall/HallMain_BP.HallMain_BP_C'"));
	//����ͼBP��ֵ��C++��
	MainHallClass = MainHall_BPClass.Class;
}

void ATowerDefenceHallHUD::BeginPlay()
{
	Super::BeginPlay();
	
	//������ͼ���ܵ�CreateWidget
	MainHall = CreateWidget<UUI_MainHall>(GetWorld(), MainHallClass);
	MainHall->AddToViewport();
}
