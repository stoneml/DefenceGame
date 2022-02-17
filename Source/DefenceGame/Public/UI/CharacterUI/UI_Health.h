// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Core/UI_RuleOfTheWidget.h"
#include "UI_Health.generated.h"

/**
 * 
 */
UCLASS()
class DEFENCEGAME_API UUI_Health : public UUI_RuleOfTheWidget
{
	GENERATED_BODY()


public:

	virtual void NativeConstruct() override;

	//…Ë÷√—™Ãıƒ⁄»›

	void SetTitle(const FString& InTitle);

	void SetHealth(float InHealth);


private:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* NameTitle;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar;

	
};
