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

	//Task节点调用函数
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;

	//初始化函数资源（很关键）
	/** initialize any asset related data */
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;


public:

	//创建一个提供给蓝图使用的黑板节点
	UPROPERTY(EditAnywhere,Category = Blackboard)
	struct FBlackboardKeySelector Blackboard_Actor;

	
};
