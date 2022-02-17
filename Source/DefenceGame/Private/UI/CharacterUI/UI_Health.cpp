// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CharacterUI/UI_Health.h"
#include "UObject/NameTypes.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"


void UUI_Health::NativeConstruct()
{
	Super::NativeConstruct();
}

void UUI_Health::SetTitle(const FString& InTitle)
{
	NameTitle->SetText(FText::FromString(InTitle));
}

void UUI_Health::SetHealth(float InHealth)
{
	HealthBar->SetPercent(InHealth);
}
