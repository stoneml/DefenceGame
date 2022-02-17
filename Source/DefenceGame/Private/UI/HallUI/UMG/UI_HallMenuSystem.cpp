// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HallUI/UMG/UI_HallMenuSystem.h"
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetSystemLibrary.h>

void UUI_HallMenuSystem::NativeConstruct()
{
	Super::NativeConstruct();

	//绑定按钮
	//这是代理绑定（UE4核心技术进阶）
/*
	GameStartButton->OnReleased.AddDynamic(this, &UUI_HallMenuSystem::GameStart);
	SecretTerritoryButton->OnReleased.AddDynamic(this, &UUI_HallMenuSystem::SecretTerritory);
	HistoryButton->OnReleased.AddDynamic(this, &UUI_HallMenuSystem::GameSettings);
	GameSettingsButton->OnReleased.AddDynamic(this, &UUI_HallMenuSystem::GameSettings);
	TutorialWebsiteButton->OnReleased.AddDynamic(this, &UUI_HallMenuSystem::TutorialsWebsite);
	BrowerButton->OnReleased.AddDynamic(this, &UUI_HallMenuSystem::Brower);
	SpecialContentButton->OnReleased.AddDynamic(this, &UUI_HallMenuSystem::SpecialContent);
	QuitGameButton->OnReleased.AddDynamic(this, &UUI_HallMenuSystem::QuitGame);
	*/

}

void UUI_HallMenuSystem::BindGameStart(FOnButtonReleasedEvent ReleaseEvent)
{
	GameStartButton->OnReleased = ReleaseEvent;
}

void UUI_HallMenuSystem::BindSecretTerritory(FOnButtonReleasedEvent ReleaseEvent)
{
	SecretTerritoryButton->OnReleased = ReleaseEvent;
}

void UUI_HallMenuSystem::BindHistory(FOnButtonReleasedEvent ReleaseEvent)
{
	HistoryButton->OnReleased = ReleaseEvent;
}

void UUI_HallMenuSystem::BindGameSettings(FOnButtonReleasedEvent ReleaseEvent)
{
	GameSettingsButton->OnReleased = ReleaseEvent;
}

void UUI_HallMenuSystem::BindTutorialWebsite(FOnButtonReleasedEvent ReleaseEvent)
{
	TutorialWebsiteButton->OnReleased = ReleaseEvent;
}

void UUI_HallMenuSystem::BindBrower(FOnButtonReleasedEvent ReleaseEvent)
{
	BrowerButton->OnReleased = ReleaseEvent;
}

void UUI_HallMenuSystem::BindSpecialContent(FOnButtonReleasedEvent ReleaseEvent)
{
	SpecialContentButton->OnReleased = ReleaseEvent;
}

void UUI_HallMenuSystem::BindQuitGame(FOnButtonReleasedEvent ReleaseEvent)
{
	QuitGameButton->OnReleased = ReleaseEvent;
}

