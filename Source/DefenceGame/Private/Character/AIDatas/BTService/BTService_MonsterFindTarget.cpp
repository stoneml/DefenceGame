// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AIDatas/BTService/BTService_MonsterFindTarget.h"
#include <BehaviorTree/BehaviorTreeComponent.h>
#include <Character/AIController/MonsterAIController.h>
#include <BrainComponent.h>
#include <Character/Core/RuleOfTheCharacter.h>
#include <BehaviorTree/BlackboardComponent.h>
#include <GameFramework/CharacterMovementComponent.h>

void UBTService_MonsterFindTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	//获取当前所有者对应的AIController
	//获取当前的黑板组件通过OwnerComp
	//通过Controller的findtarget来获取到当前的目标
	//判断如果新目标不是当前目标，就把获取到的目标设置给Target
	// {  通过AIController获取到当前Monster自己
	//		通过是用移动组件的StopMovementImmediately来停止移动
	//	}
	//判断当前Target是否是有效的
	//如果有效{  }


	//获取当前所有着对应的AIController
	//AMonsterAIController* MonsterAIController = Cast<AMonsterAIController>(OwnerComp.GetOwner(),如果只针对查找Monster的话。
	if (ARuleOfTheAIController* MonsterAIController = Cast<ARuleOfTheAIController>(OwnerComp.GetOwner()))
	{
		//获取当前所有者（OwnerComp）的黑板
		if (UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent())
		{
			//通过当前AIController获取到当前目标
			if (ARuleOfTheCharacter* NewTarget = Cast<ARuleOfTheCharacter>(MonsterAIController->FindTarget()))
			{
				//如果获取到的目标不是当前目标
				if (NewTarget!= MonsterAIController->CurrentTarget)
				{
					//通过AIController获取当拥有者Pawn，立即停止移动，然后进行目标切换
					if (ARuleOfTheCharacter* MonsterSelf = Cast<ARuleOfTheCharacter>(MonsterAIController->GetPawn()))
					{
						//Stop 立即停止
						MonsterSelf->GetMovementComponent()->StopMovementImmediately();
					}
					//新目标赋值
					MonsterAIController->CurrentTarget = NewTarget;
				}

				//新目标赋值给黑板
				//判断当前目标（无论新旧）是否有效
				if (MonsterAIController->CurrentTarget.IsValid())
				{
					if (MonsterAIController->CurrentTarget->IsActive()) //如果目标还活着
					{

						/*
						//进行一个简单的距离位置设定
						FVector CurrentFaceVecter = MonsterAIController->GetPawn()->GetActorLocation() - Target.Get()->GetActorLocation();	
						CurrentFaceVecter.Normalize();
						FVector MonsterAttackPos =CurrentFaceVecter * 800.f + Target.Get()->GetActorLocation();
						MyBlackboard->SetValueAsVector(BlackBoardKey_TargetLocation.SelectedKeyName, MonsterAttackPos);
						*/
						
						MyBlackboard->SetValueAsObject(BlackBoardKey_Target.SelectedKeyName, MonsterAIController->CurrentTarget.Get());  //target.Get（）是弱指针获取裸指针的方法
						//找到目标后就返回目标位置
						MyBlackboard->SetValueAsVector(BlackBoardKey_TargetLocation.SelectedKeyName, MonsterAIController->CurrentTarget.Get()->GetActorLocation());
					}
					else
					{
						MyBlackboard->SetValueAsObject(BlackBoardKey_Target.SelectedKeyName, nullptr);
						MyBlackboard->SetValueAsVector(BlackBoardKey_TargetLocation.SelectedKeyName, FVector::ZeroVector);
					}
				}
				else
				{
					MyBlackboard->SetValueAsObject(BlackBoardKey_Target.SelectedKeyName, nullptr);
					MyBlackboard->SetValueAsVector(BlackBoardKey_TargetLocation.SelectedKeyName, FVector::ZeroVector);
				}
				
			}
			else
			{
				//如果无法从Controller中获取新目标，那么就返回为空
				MyBlackboard->SetValueAsObject(BlackBoardKey_Target.SelectedKeyName, nullptr);
			}


			//计算距离
			if (MonsterAIController->CurrentTarget.IsValid())
			{
				//获取当前Monster距离
				FVector MyLocation = MonsterAIController->GetPawn()->GetActorLocation();
				FVector TMDistance = MyLocation - MonsterAIController->CurrentTarget->GetActorLocation();

				if (ARuleOfTheCharacter* MonsterAI = Cast<ARuleOfTheCharacter>(MonsterAIController->GetPawn()))
				{
					//设定一个距离
					if (TMDistance.Size() >= 800)
					{
						//如果距离大于800就停止攻击
						MonsterAI->bAttack = false;
					}
					else
					{
						//如果不小于那么就停止，之后开始进行攻击。（攻击逻辑在Task中进行执行）
						MonsterAI->GetMovementComponent()->StopMovementImmediately();
					}
				}
				//将当前距离返回出去
				MyBlackboard->SetValueAsFloat(BlackBoardKey_Distance.SelectedKeyName, TMDistance.Size());
			}
			else
			{
				//如果目标无效，返回距离为0
				MyBlackboard->SetValueAsFloat(BlackBoardKey_Distance.SelectedKeyName, 0.0f);
			}
		}
	}
}
