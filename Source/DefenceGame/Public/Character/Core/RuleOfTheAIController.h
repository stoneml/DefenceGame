// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "RuleOfTheAIController.generated.h"

/**
 * 
 */
UCLASS()
class DEFENCEGAME_API ARuleOfTheAIController : public AAIController
{
	GENERATED_BODY()


public:

	//返回目标Actor 让子类去继承
	virtual AActor* FindTarget() { return nullptr; };

	//AIController的攻击函数
	virtual void AttackTarget(ARuleOfTheCharacter* Target) {};
	
	//Controller获取目标
	TWeakObjectPtr<class ARuleOfTheCharacter> CurrentTarget;

};
