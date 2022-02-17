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

	//��ȡ��ǰ�����߶�Ӧ��AIController
	//��ȡ��ǰ�ĺڰ����ͨ��OwnerComp
	//ͨ��Controller��findtarget����ȡ����ǰ��Ŀ��
	//�ж������Ŀ�겻�ǵ�ǰĿ�꣬�Ͱѻ�ȡ����Ŀ�����ø�Target
	// {  ͨ��AIController��ȡ����ǰMonster�Լ�
	//		ͨ�������ƶ������StopMovementImmediately��ֹͣ�ƶ�
	//	}
	//�жϵ�ǰTarget�Ƿ�����Ч��
	//�����Ч{  }


	//��ȡ��ǰ�����Ŷ�Ӧ��AIController
	//AMonsterAIController* MonsterAIController = Cast<AMonsterAIController>(OwnerComp.GetOwner(),���ֻ��Բ���Monster�Ļ���
	if (ARuleOfTheAIController* MonsterAIController = Cast<ARuleOfTheAIController>(OwnerComp.GetOwner()))
	{
		//��ȡ��ǰ�����ߣ�OwnerComp���ĺڰ�
		if (UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent())
		{
			//ͨ����ǰAIController��ȡ����ǰĿ��
			if (ARuleOfTheCharacter* NewTarget = Cast<ARuleOfTheCharacter>(MonsterAIController->FindTarget()))
			{
				//�����ȡ����Ŀ�겻�ǵ�ǰĿ��
				if (NewTarget!= MonsterAIController->CurrentTarget)
				{
					//ͨ��AIController��ȡ��ӵ����Pawn������ֹͣ�ƶ���Ȼ�����Ŀ���л�
					if (ARuleOfTheCharacter* MonsterSelf = Cast<ARuleOfTheCharacter>(MonsterAIController->GetPawn()))
					{
						//Stop ����ֹͣ
						MonsterSelf->GetMovementComponent()->StopMovementImmediately();
					}
					//��Ŀ�긳ֵ
					MonsterAIController->CurrentTarget = NewTarget;
				}

				//��Ŀ�긳ֵ���ڰ�
				//�жϵ�ǰĿ�꣨�����¾ɣ��Ƿ���Ч
				if (MonsterAIController->CurrentTarget.IsValid())
				{
					if (MonsterAIController->CurrentTarget->IsActive()) //���Ŀ�껹����
					{

						/*
						//����һ���򵥵ľ���λ���趨
						FVector CurrentFaceVecter = MonsterAIController->GetPawn()->GetActorLocation() - Target.Get()->GetActorLocation();	
						CurrentFaceVecter.Normalize();
						FVector MonsterAttackPos =CurrentFaceVecter * 800.f + Target.Get()->GetActorLocation();
						MyBlackboard->SetValueAsVector(BlackBoardKey_TargetLocation.SelectedKeyName, MonsterAttackPos);
						*/
						
						MyBlackboard->SetValueAsObject(BlackBoardKey_Target.SelectedKeyName, MonsterAIController->CurrentTarget.Get());  //target.Get��������ָ���ȡ��ָ��ķ���
						//�ҵ�Ŀ���ͷ���Ŀ��λ��
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
				//����޷���Controller�л�ȡ��Ŀ�꣬��ô�ͷ���Ϊ��
				MyBlackboard->SetValueAsObject(BlackBoardKey_Target.SelectedKeyName, nullptr);
			}


			//�������
			if (MonsterAIController->CurrentTarget.IsValid())
			{
				//��ȡ��ǰMonster����
				FVector MyLocation = MonsterAIController->GetPawn()->GetActorLocation();
				FVector TMDistance = MyLocation - MonsterAIController->CurrentTarget->GetActorLocation();

				if (ARuleOfTheCharacter* MonsterAI = Cast<ARuleOfTheCharacter>(MonsterAIController->GetPawn()))
				{
					//�趨һ������
					if (TMDistance.Size() >= 800)
					{
						//����������800��ֹͣ����
						MonsterAI->bAttack = false;
					}
					else
					{
						//�����С����ô��ֹͣ��֮��ʼ���й������������߼���Task�н���ִ�У�
						MonsterAI->GetMovementComponent()->StopMovementImmediately();
					}
				}
				//����ǰ���뷵�س�ȥ
				MyBlackboard->SetValueAsFloat(BlackBoardKey_Distance.SelectedKeyName, TMDistance.Size());
			}
			else
			{
				//���Ŀ����Ч�����ؾ���Ϊ0
				MyBlackboard->SetValueAsFloat(BlackBoardKey_Distance.SelectedKeyName, 0.0f);
			}
		}
	}
}
