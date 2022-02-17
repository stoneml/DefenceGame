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

	//继承父类的找到目标
	virtual AActor* FindTarget() override;

	//继承攻击函数
	virtual void AttackTarget(ARuleOfTheCharacter* Target) override;

protected:

	//模拟一个Service
	void BTService_FindTarget();



protected:

	//这里是怪物
	UPROPERTY()
		TArray<ARuleOfTheCharacter*> TarryMonster;

	//这个Target目标暂时取消，由RuleOfAIController中的Target替代。
	//获取当前目标(为了旋转而设置）
	//TWeakObjectPtr<ARuleOfTheCharacter> CurrentTarget;

	//用来作为心跳的间隔
	float HeartbeatDiagnosis;


	
};
