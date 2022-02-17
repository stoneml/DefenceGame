// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Core/UI_RuleOfTheWidget.h"
#include "UI_ICODragDrop.generated.h"

/**
 * 
 */


class UImage;

UCLASS()
class DEFENCEGAME_API UUI_ICODragDrop : public UUI_RuleOfTheWidget
{
	GENERATED_BODY()
	

private:

	UPROPERTY(meta = (BindWidget))
	UImage* SlotIcon;


public:

	//������קͼ���ͼƬ
	void SetDrawICON(UTexture2D* InIcon);



};
