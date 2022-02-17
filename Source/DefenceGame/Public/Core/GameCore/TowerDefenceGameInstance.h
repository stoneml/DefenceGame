// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TowerDefenceGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DEFENCEGAME_API UTowerDefenceGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	//��ʼ��GameInstance
	virtual void Init() override;

};
