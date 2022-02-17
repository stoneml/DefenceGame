// Copyright Epic Games, Inc. All Rights Reserved.


#include "DefenceGameGameModeBase.h"
#include <Core/GameCore/TowerDefenceGameState.h>
#include <Core/GameCore/TowerDefenceGamePlayerController.h>
#include <Core/GameCore/TowerDefencePlayerState.h>
#include "UI/GameUI/Core/RuleOfTheHUD.h"
#include <Core/GameCore/TowerDefenceGameCamera.h>

ADefenceGameGameModeBase::ADefenceGameGameModeBase()
{

	//加载GameState
	GameStateClass = ATowerDefenceGameState::StaticClass();

	//加载Controller
	PlayerControllerClass = ATowerDefenceGamePlayerController::StaticClass();

	//加载ControllerPawn
	DefaultPawnClass = ATowerDefenceGameCamera::StaticClass();

	//加载PlayerState
	PlayerStateClass = ATowerDefencePlayerState::StaticClass();

	//加载HUD
	HUDClass = ARuleOfTheHUD::StaticClass();



}
