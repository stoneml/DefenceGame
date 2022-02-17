// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterCore/Monster.h"

void AMonster::BeginPlay()
{
	Super::BeginPlay();

}

void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

EGameCharacterType::Type AMonster::GetType()
{
	return EGameCharacterType::Type::MONSTER;
}
