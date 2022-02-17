// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskAttackTarget.generated.h"

/**
 * 
 */
UCLASS()
class DEFENCEGAME_API UBTTaskAttackTarget : public UBTTaskNode
{
	GENERATED_BODY()

public:

	/** Notify called after GameplayTask finishes initialization (not active yet) */
	virtual void OnGameplayTaskInitialized(UGameplayTask& Task) {}

	/** Notify called after GameplayTask changes state to Active (initial activation or resuming) */
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) {}

	/** Notify called after GameplayTask changes state from Active (finishing or pausing) */
	virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) {}


public:

	//Task�ڵ���ú���
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;

	//��ʼ��������Դ���ܹؼ���
	/** initialize any asset related data */
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;


public:

	//����һ���ṩ����ͼʹ�õĺڰ�ڵ�
	UPROPERTY(EditAnywhere,Category = Blackboard)
	struct FBlackboardKeySelector Blackboard_Actor;

	
};
