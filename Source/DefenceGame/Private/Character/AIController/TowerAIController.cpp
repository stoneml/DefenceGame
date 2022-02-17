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
		//ִ��һ������
		BTService_FindTarget();
		HeartbeatDiagnosis = 0.0f;
	}

	if (TarryMonster.Num()>0)
	{
		//ͨ��GetPawn����ȡ���Լ���
		if (ATowers* Tower = GetPawn<ATowers>())
		{
			//��Ŀ����Ч����Ŀ�������󣬾Ϳ�ʼ������Ŀ��
			if (!CurrentTarget.IsValid()||!CurrentTarget->IsActive())
			{
				//���Ŀ����Ч����ô�Ϳ�ʼ����Ŀ��
				CurrentTarget = Cast<ARuleOfTheCharacter>(FindTarget());
			}

			//��ΪTarget�ᱻ���գ���������Ҫ����һ����Ч���ж�
			if (CurrentTarget.IsValid())
			{
				//ʹ��UE����ת���󣬻�õ�ǰ����תֵ(ͨ����������������ת����
				Tower->TowerRotaotor =FRotationMatrix::MakeFromX(CurrentTarget->GetActorLocation() - GetPawn()->GetActorLocation()).Rotator();

				Tower->bAttack = true;  //���Ŀ��Ϊ��ͽ��й�����

				//�õ�����ת��λ��
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
		//����λ���ж�
		return DefenceGameUtils::FindTargetRecently(TarryMonster, GetPawn()->GetActorLocation());
	}

	return nullptr;
}




void ATowerAIController::BTService_FindTarget()
{
	//ÿ�β�������յ�ǰ��ѯ����
	TarryMonster.Empty();

	if (ATowers*Tower = GetPawn<ATowers>())
	{
		//������Լ�����
		if (Tower->IsActive())
		{
			//ʹ��Actor������������Ŀ�����
			for (TActorIterator<AMonster> It(GetWorld(), AMonster::StaticClass()); It; ++It)
			{
				if (AMonster* TheCharacter = *It)
				{
					if (TheCharacter->IsActive())
					{
						//Ŀ���λ�ú��Լ�����һ������
						FVector TDistace = TheCharacter->GetActorLocation() - GetPawn()->GetActorLocation();
						if (TDistace.Size() <= 1600)
						{
							TarryMonster.Add(TheCharacter);
						}
					}
				}
			}

			//��Ŀ�����һ��žͿ�ʼ���й���
			//��ָ��ת��
			AttackTarget(CurrentTarget.Get());
		}
	}
}


void ATowerAIController::AttackTarget(ARuleOfTheCharacter* Target)
{
	//��ȡTower���͵�Pawn�������ߣ�
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