// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "SpawnPoint.generated.h"

/**
 * 
 */
UCLASS()
class DEFENCEGAME_API ASpawnPoint : public ATargetPoint
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;
	
};
