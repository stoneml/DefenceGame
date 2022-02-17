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

	//�̳и�����ҵ�Ŀ��
	virtual AActor* FindTarget()override;

	//��������
	virtual void AttackTarget(ARuleOfTheCharacter* Target)override;

};