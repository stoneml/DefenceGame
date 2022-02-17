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

	//��дAnimInstance�еĺ���

	virtual void NativeInitializeAnimation();

	//�������tick
	virtual void NativeUpdateAnimation(float DeltaSeconds);


public:

	//�����ֵ�Ǵ��ݸ�������ͼʹ�õ�

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimAttribute")
		bool bAttack;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimAttribute")
		bool bDeath;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimAttribute")
		float Speed;


};
