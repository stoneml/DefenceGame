// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Core/UI_RuleOfTheWidget.h"
#include "UObject/NoExportTypes.h"
#include "Core/GameCore/TowerDefenceGamePlayerController.h"


UUI_RuleOfTheWidget::UUI_RuleOfTheWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	CurrentGUID = FGuid::NewGuid();
}

class ATowerDefenceGameState* UUI_RuleOfTheWidget::GetGameState()
{
	if (GetWorld())
	{
		//����ָ�����͵�GameState
		return GetWorld()->GetGameState<ATowerDefenceGameState>();
		
	}
	return nullptr;
}

class ATowerDefenceGamePlayerController* UUI_RuleOfTheWidget::GetPlayerController()
{
	if (GetWorld())
	{
		//����ָ�����͵�PlayerController
		return GetWorld()->GetFirstPlayerController<ATowerDefenceGamePlayerController>();
	}
	return nullptr;
}

