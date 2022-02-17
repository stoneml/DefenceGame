// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Core/UI_RuleOfTheWidget.h"
#include "UI_RucksackSystem.generated.h"

/**
 * 
 */

class UUI_Inventory;

UCLASS()
class DEFENCEGAME_API UUI_RucksackSystem : public UUI_RuleOfTheWidget
{
	GENERATED_BODY()
	


private:

	//创建一个背包
	UPROPERTY(meta = (BindWidget))
		UUI_Inventory* Inventroy;


public:

	virtual void NativeConstruct();

};
