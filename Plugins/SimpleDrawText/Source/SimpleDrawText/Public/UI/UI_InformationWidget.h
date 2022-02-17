// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_InformationWidget.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEDRAWTEXT_API UUI_InformationWidget : public UUserWidget
{
	GENERATED_BODY()


public:

	//用来设定文字内容
	void SetTextBlockStyle(const FString& InText, const FLinearColor& InColor, float InPercentage);


protected:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextWidget;


	
};
