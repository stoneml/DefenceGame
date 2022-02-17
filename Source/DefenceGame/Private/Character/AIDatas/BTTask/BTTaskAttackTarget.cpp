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

	//获得当前AIController
	//通过OwnerComp获取当前黑板组件
	//判断Blackboard_Actor的类型是否是黑板类型的object类型
	//获取当前Controller的控制者Pawn(转换类型为ARuleOfTheCharacter)
	//通过黑板获取当前的目标(目标为ARuleOfTheCharacter)
	//如果有目标那么就进行攻击，如果没目标就不进行攻击


	//行为树的所有者就是AIController
	if (AMonsterAIController*MyAIController =Cast<AMonsterAIController>(OwnerComp.GetOwner()))
	{
		if (UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent())
		{
			//获取黑板资源(如果Actor是黑板的Object资源)
			if (Blackboard_Actor.SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
			{
				//获取当前Controller的拥有者
				if (ARuleOfTheCharacter* MyPawn = Cast<ARuleOfTheCharacter>(MyAIController->GetPawn()))
				{
					//获取当前行黑板的目标
					if (ARuleOfTheCharacter* TargetTower = Cast<ARuleOfTheCharacter>(MyBlackboard->GetValueAsObject(Blackboard_Actor.SelectedKeyName)))
					{
						//怪物开始攻击
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

	//执行不成功就返回Failed
	return EBTNodeResult::Failed;

}

void UBTTaskAttackTarget::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	if (UBlackboardData* BBAsset = GetBlackboardAsset())
	{
		//*是将指针内的东西拿出来给他
		Blackboard_Actor.ResolveSelectedKey(*BBAsset);
	}
	else
	{
		//无法解析就发出消息
		UE_LOG(LogBehaviorTree, Warning, TEXT("Can't Initialize task:%s"), *GetName());
	}


}
