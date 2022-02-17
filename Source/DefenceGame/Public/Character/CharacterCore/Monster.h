// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Core/RuleOfTheCharacter.h"
#include "Monster.generated.h"

/**
 * 
 */
UCLASS()
class DEFENCEGAME_API AMonster : public ARuleOfTheCharacter
{
	GENERATED_BODY()
	

public:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime)override;

	//Monster�Ķ�����false
	virtual bool IsTeam() { return Super::IsTeam(); }

	//�̳и���ĺ���
	virtual EGameCharacterType::Type GetType();

};
