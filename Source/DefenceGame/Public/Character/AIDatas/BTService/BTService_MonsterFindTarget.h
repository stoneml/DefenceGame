// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_MonsterFindTarget.generated.h"

/**
 * 
 */
UCLASS()
class DEFENCEGAME_API UBTService_MonsterFindTarget : public UBTService
{
	GENERATED_BODY()

public:

	//使用父类Tick
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	//创建在蓝图中可以添加的参数

	//AI目标
	UPROPERTY(EditAnywhere, Category = "Blackboard")
		struct FBlackboardKeySelector BlackBoardKey_Target;

	//目标距离
	UPROPERTY(EditAnywhere, Category = "Blackboard")
		struct FBlackboardKeySelector BlackBoardKey_Distance;

	//目标位置
	UPROPERTY(EditAnywhere, Category = "BlackBoard")
		struct FBlackboardKeySelector BlackBoardKey_TargetLocation;

	/** Notify called after GameplayTask finishes initialization (not active yet) */
	virtual void OnGameplayTaskInitialized(UGameplayTask& Task) {}

	/** Notify called after GameplayTask changes state to Active (initial activation or resuming) */
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) {}

	/** Notify called after GameplayTask changes state from Active (finishing or pausing) */
	virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) {}


private:

	//使用弱指针创建目标变量，弱指针在无效后会自动置空，可以确保不会出现野指针
	TWeakObjectPtr <class ARuleOfTheCharacter> Target;
	
};
