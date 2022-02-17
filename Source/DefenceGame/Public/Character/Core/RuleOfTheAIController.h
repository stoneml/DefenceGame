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

	//����Ŀ��Actor ������ȥ�̳�
	virtual AActor* FindTarget() { return nullptr; };

	//AIController�Ĺ�������
	virtual void AttackTarget(ARuleOfTheCharacter* Target) {};
	
	//Controller��ȡĿ��
	TWeakObjectPtr<class ARuleOfTheCharacter> CurrentTarget;

};
