// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Core/RuleOfTheAIController.h"
#include "TowerAIController.generated.h"

/**
 * 
 */

class ARuleOfTheCharacter;


UCLASS()
class DEFENCEGAME_API ATowerAIController : public ARuleOfTheAIController
{
	GENERATED_BODY()


public:
	ATowerAIController();

	//Called every frame
	virtual void Tick(float DeltaTime) override;

	//�̳и�����ҵ�Ŀ��
	virtual AActor* FindTarget() override;

	//�̳й�������
	virtual void AttackTarget(ARuleOfTheCharacter* Target) override;

protected:

	//ģ��һ��Service
	void BTService_FindTarget();



protected:

	//�����ǹ���
	UPROPERTY()
		TArray<ARuleOfTheCharacter*> TarryMonster;

	//���TargetĿ����ʱȡ������RuleOfAIController�е�Target�����
	//��ȡ��ǰĿ��(Ϊ����ת�����ã�
	//TWeakObjectPtr<ARuleOfTheCharacter> CurrentTarget;

	//������Ϊ�����ļ��
	float HeartbeatDiagnosis;


	
};
