// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AIDatas/BTTask/BTTaskAttackTarget.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Character/AIController/MonsterAIController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/Core/RuleOfTheCharacter.h"


EBTNodeResult::Type UBTTaskAttackTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	//��õ�ǰAIController
	//ͨ��OwnerComp��ȡ��ǰ�ڰ����
	//�ж�Blackboard_Actor�������Ƿ��Ǻڰ����͵�object����
	//��ȡ��ǰController�Ŀ�����Pawn(ת������ΪARuleOfTheCharacter)
	//ͨ���ڰ��ȡ��ǰ��Ŀ��(Ŀ��ΪARuleOfTheCharacter)
	//�����Ŀ����ô�ͽ��й��������ûĿ��Ͳ����й���


	//��Ϊ���������߾���AIController
	if (AMonsterAIController*MyAIController =Cast<AMonsterAIController>(OwnerComp.GetOwner()))
	{
		if (UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent())
		{
			//��ȡ�ڰ���Դ(���Actor�Ǻڰ��Object��Դ)
			if (Blackboard_Actor.SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
			{
				//��ȡ��ǰController��ӵ����
				if (ARuleOfTheCharacter* MyPawn = Cast<ARuleOfTheCharacter>(MyAIController->GetPawn()))
				{
					//��ȡ��ǰ�кڰ��Ŀ��
					if (ARuleOfTheCharacter* TargetTower = Cast<ARuleOfTheCharacter>(MyBlackboard->GetValueAsObject(Blackboard_Actor.SelectedKeyName)))
					{
						//���￪ʼ����
						MyPawn->bAttack = true;
						MyAIController->AttackTarget(TargetTower);
						return EBTNodeResult::Succeeded;
					}
					else
					{
						MyPawn->bAttack = false;
						return EBTNodeResult::Succeeded;
					}
				}
			}
		}
	}

	//ִ�в��ɹ��ͷ���Failed
	return EBTNodeResult::Failed;

}

void UBTTaskAttackTarget::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	if (UBlackboardData* BBAsset = GetBlackboardAsset())
	{
		//*�ǽ�ָ���ڵĶ����ó�������
		Blackboard_Actor.ResolveSelectedKey(*BBAsset);
	}
	else
	{
		//�޷������ͷ�����Ϣ
		UE_LOG(LogBehaviorTree, Warning, TEXT("Can't Initialize task:%s"), *GetName());
	}


}
