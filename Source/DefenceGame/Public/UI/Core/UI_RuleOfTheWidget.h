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

	//��ҪԤ����ID
	UUI_RuleOfTheWidget(const FObjectInitializer& ObjectInitializer);

	//�����д�����Widget����һ��ID

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = UI)
	FGuid CurrentGUID;


	//��ȡ��ǰGameState
	class ATowerDefenceGameState* GetGameState();
	class ATowerDefenceGamePlayerController* GetPlayerController();


};
