// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameUI/UMG/UI_GameMenuSystem.h"
#include <Components/Button.h>

void UUI_GameMenuSystem::NativeConstruct()
{
	Super::NativeConstruct();


	//°ó¶¨°´Å¥°´¼ü
	ReturnGameButton->OnReleased.AddDynamic(this, &UUI_GameMenuSystem::ReturnGame);
	SaveGameButton->OnReleased.AddDynamic(this, &UUI_GameMenuSystem::SaveGame);
	GameSettingButton->OnReleased.AddDynamic(this, &UUI_GameMenuSystem::GameSetting);
	GameQuitButton->OnReleased.AddDynamic(this, &UUI_GameMenuSystem::GameQuit);

}

void UUI_GameMenuSystem::ReturnGame()
{

}

void UUI_GameMenuSystem::SaveGame()
{

}

void UUI_GameMenuSystem::GameSetting()
{

}

void UUI_GameMenuSystem::GameQuit()
{

}
