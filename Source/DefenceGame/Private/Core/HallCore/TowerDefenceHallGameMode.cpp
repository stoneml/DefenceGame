// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/HallCore/TowerDefenceHallGameMode.h"
#include <UI/HallUI/Core/TowerDefenceHallHUD.h>
#include <Core/HallCore/TowerDefenceHallPawn.h>
#include <Core/HallCore/TowerDefenceHallPlayerController.h>

ATowerDefenceHallGameMode::ATowerDefenceHallGameMode()
{
	
	HUDClass = ATowerDefenceHallHUD::StaticClass();
	DefaultPawnClass = ATowerDefenceHallPawn::StaticClass();
	PlayerControllerClass = ATowerDefenceHallPlayerController::StaticClass();

}
