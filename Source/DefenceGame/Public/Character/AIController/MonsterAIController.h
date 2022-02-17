// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Core/RuleOfTheAIController.h"
#include "MonsterAIController.generated.h"

/**
 * 
 */
UCLASS()
class DEFENCEGAME_API AMonsterAIController : public ARuleOfTheAIController
{
	GENERATED_BODY()
	

public:

	//继承父类的找到目标
	virtual AActor* FindTarget()override;

	//攻击函数
	virtual void AttackTarget(ARuleOfTheCharacter* Target)override;

};
