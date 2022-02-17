// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Anim/RuleOfTheAnimInstace.h"
#include <Character/Core/RuleOfTheCharacter.h>
#include "Character/CharacterCore/Towers.h"

URuleOfTheAnimInstace::URuleOfTheAnimInstace()
	:bAttack(false)
	,bDeath(false)
	,Speed(0.0f)
{

}

void URuleOfTheAnimInstace::NativeInitializeAnimation()
{
	Super::NativeUninitializeAnimation();
}

void URuleOfTheAnimInstace::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	ARuleOfTheCharacter* RuleOfTheCharacter = Cast<ARuleOfTheCharacter>(TryGetPawnOwner());
	if (RuleOfTheCharacter)
	{
		bAttack = RuleOfTheCharacter->bAttack;
		bDeath = !RuleOfTheCharacter->IsActive();
		Speed = RuleOfTheCharacter->GetVelocity().Size();  //这里的.size就是蓝图中的vector length
	}
}
