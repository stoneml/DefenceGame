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

	//ʹ�ø���Tick
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	//��������ͼ�п�����ӵĲ���

	//AIĿ��
	UPROPERTY(EditAnywhere, Category = "Blackboard")
		struct FBlackboardKeySelector BlackBoardKey_Target;

	//Ŀ�����
	UPROPERTY(EditAnywhere, Category = "Blackboard")
		struct FBlackboardKeySelector BlackBoardKey_Distance;

	//Ŀ��λ��
	UPROPERTY(EditAnywhere, Category = "BlackBoard")
		struct FBlackboardKeySelector BlackBoardKey_TargetLocation;

	/** Notify called after GameplayTask finishes initialization (not active yet) */
	virtual void OnGameplayTaskInitialized(UGameplayTask& Task) {}

	/** Notify called after GameplayTask changes state to Active (initial activation or resuming) */
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) {}

	/** Notify called after GameplayTask changes state from Active (finishing or pausing) */
	virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) {}


private:

	//ʹ����ָ�봴��Ŀ���������ָ������Ч����Զ��ÿգ�����ȷ���������Ұָ��
	TWeakObjectPtr <class ARuleOfTheCharacter> Target;
	
};
