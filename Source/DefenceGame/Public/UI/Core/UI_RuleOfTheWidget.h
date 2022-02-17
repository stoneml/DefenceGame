// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_RuleOfTheWidget.generated.h"

/**
 * 
 */
UCLASS()
class DEFENCEGAME_API UUI_RuleOfTheWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:

	//需要预创建ID
	UUI_RuleOfTheWidget(const FObjectInitializer& ObjectInitializer);

	//给所有创建的Widget创建一个ID

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = UI)
	FGuid CurrentGUID;


	//获取当前GameState
	class ATowerDefenceGameState* GetGameState();
	class ATowerDefenceGamePlayerController* GetPlayerController();


};
