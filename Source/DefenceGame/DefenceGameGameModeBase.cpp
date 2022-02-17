// Copyright Epic Games, Inc. All Rights Reserved.


#include "DefenceGameGameModeBase.h"
#include <Core/GameCore/TowerDefenceGameState.h>
#include <Core/GameCore/TowerDefenceGamePlayerController.h>
#include <Core/GameCore/TowerDefencePlayerState.h>
#include "UI/GameUI/Core/RuleOfTheHUD.h"
#include <Core/GameCore/TowerDefenceGameCamera.h>

ADefenceGameGameModeBase::ADefenceGameGameModeBase()
{

	//����GameState
	GameStateClass = ATowerDefenceGameState::StaticClass();

	//����Controller
	PlayerControllerClass = ATowerDefenceGamePlayerController::StaticClass();

	//����ControllerPawn
	DefaultPawnClass = ATowerDefenceGameCamera::StaticClass();

	//����PlayerState
	PlayerStateClass = ATowerDefencePlayerState::StaticClass();

	//����HUD
	HUDClass = ARuleOfTheHUD::StaticClass();



}
