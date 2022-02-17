// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Core/UI_RuleOfTheWidget.h"
#include "UI_GameInfoPrintSystem.generated.h"

/**
 * 
 */
UCLASS()
class DEFENCEGAME_API UUI_GameInfoPrintSystem : public UUI_RuleOfTheWidget
{
	GENERATED_BODY()


private:

	//添加一个Text的绑定
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TDGameLog;

public:

	virtual void NativeConstruct();
	
};
