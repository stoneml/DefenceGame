// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/SelectLevelCore/TowerDefenceSelectLevelGameMode.h"
#include <UI/SelectLevelUI/Core/TowerDefenceSelectLevelHUD.h>
#include <Kismet/GameplayStatics.h>
#include <GameFramework/PlayerController.h>

ATowerDefenceSelectLevelGameMode::ATowerDefenceSelectLevelGameMode()
{
	//×¢²áHUD
	HUDClass = ATowerDefenceSelectLevelHUD::StaticClass();
	

}

void ATowerDefenceSelectLevelGameMode::BeginPlay()
{
	if (APlayerController* AController = UGameplayStatics::GetPlayerController(this, 0))
	{
		AController->bShowMouseCursor = true;
	}
}
