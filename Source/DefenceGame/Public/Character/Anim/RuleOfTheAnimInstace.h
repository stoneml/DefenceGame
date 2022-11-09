// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "RuleOfTheAnimInstace.generated.h"

/**
 * 
 */
UCLASS()
class DEFENCEGAME_API URuleOfTheAnimInstace : public UAnimInstance
{
	GENERATED_BODY()
	

public:

	URuleOfTheAnimInstace();

	//覆写AnimInstance中的函数
	//类似beginPlay
	virtual void NativeInitializeAnimation();

	//这个类似tick
	virtual void NativeUpdateAnimation(float DeltaSeconds);


public:

	//这里的值是传递给动画蓝图使用的

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimAttribute")
		bool bAttack;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimAttribute")
		bool bDeath;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimAttribute")
		float Speed;


};
