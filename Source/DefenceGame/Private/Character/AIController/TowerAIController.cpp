// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AIController/TowerAIController.h"
#include "Character/CharacterCore/Monster.h"
#include "Character/CharacterCore/Towers.h"
#include "EngineUtils.h"
#include "../DefenceGameUtils.h"
#include "Math/RotationMatrix.h"


ATowerAIController::ATowerAIController()
	:HeartbeatDiagnosis(0.f)
{

}

void ATowerAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HeartbeatDiagnosis += DeltaTime;
	if (HeartbeatDiagnosis>=0.5f)
	{
		//执行一次找人
		BTService_FindTarget();
		HeartbeatDiagnosis = 0.0f;
	}

	if (TarryMonster.Num()>0)
	{
		//通过GetPawn来获取到自己。
		if (ATowers* Tower = GetPawn<ATowers>())
		{
			//当目标无效或者目标死亡后，就开始吃搜索目标
			if (!CurrentTarget.IsValid()||!CurrentTarget->IsActive())
			{
				//如果目标无效，那么就开始搜索目标
				CurrentTarget = Cast<ARuleOfTheCharacter>(FindTarget());
			}

			//因为Target会被传空，所以这里要进行一次有效性判断
			if (CurrentTarget.IsValid())
			{
				//使用UE的旋转矩阵，获得当前的旋转值(通过方向向量来进行转换）
				Tower->TowerRotaotor =FRotationMatrix::MakeFromX(CurrentTarget->GetActorLocation() - GetPawn()->GetActorLocation()).Rotator();

				Tower->bAttack = true;  //如果目标为真就进行攻击。

				//拿到塔旋转的位置
				if (GetPawn()->GetActorRotation()!=FRotator::ZeroRotator)
				{
					Tower->TowerRotaotor -= GetPawn()->GetActorRotation();
				}
			}
		}
	}
}


AActor* ATowerAIController::FindTarget()
{
	if (TarryMonster.Num()>0)
	{
		//进行位置判断
		return DefenceGameUtils::FindTargetRecently(TarryMonster, GetPawn()->GetActorLocation());
	}

	return nullptr;
}


void ATowerAIController::BTService_FindTarget()
{
	//每次查找先清空当前查询数组
	TarryMonster.Empty();

	if (ATowers*Tower = GetPawn<ATowers>())
	{
		//如果我自己活着
		if (Tower->IsActive())
		{
			//使用Actor迭代器来进行目标查找
			for (TActorIterator<AMonster> It(GetWorld(), AMonster::StaticClass()); It; ++It)
			{
				if (AMonster* TheCharacter = *It)
				{
					if (TheCharacter->IsActive())
					{
						//目标的位置和自己进行一个换算
						FVector TDistace = TheCharacter->GetActorLocation() - GetPawn()->GetActorLocation();
						if (TDistace.Size() <= 1600)
						{
							TarryMonster.Add(TheCharacter);
						}
					}
				}
			}

			//有目标且我活着就开始进行攻击
			//弱指针转换
			AttackTarget(CurrentTarget.Get());
		}
	}
}


void ATowerAIController::AttackTarget(ARuleOfTheCharacter* Target)
{
	//获取Tower类型的Pawn（所有者）
	if (ATowers* Tower = GetPawn<ATowers>())
	{
		if (TarryMonster.Num() > 0)
		{
			Tower->bAttack = true;
		}
		else
		{
			Tower->bAttack = false;
		}
	}

	
}