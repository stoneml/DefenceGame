// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RuleOfTheHUD.generated.h"

/**
 * 
 */

class UUI_MainScreen;

UCLASS()
class DEFENCEGAME_API ARuleOfTheHUD : public AHUD
{
	GENERATED_BODY()

public:

	ARuleOfTheHUD();


	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ShowMainUI();

private:

	TSubclassOf<UUI_MainScreen>MainScreenClass;

	UUI_MainScreen* MainScreen;

	
};
