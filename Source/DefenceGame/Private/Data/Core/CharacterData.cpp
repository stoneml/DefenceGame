// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Core/CharacterData.h"


FCharacterData::FCharacterData()
	:Name(NAME_None),
	CharacterID(INDEX_NONE),
//GUID(FGuid::NewGuid().ToString()), //¹þÏ£ÖµµÄGUID
	CurLevel(1),
	MaxHealth(400.f),
	Health(MaxHealth),
	PhysicalAttack(10.f),
	AttackSpeed(0.66),
	Armor(10.f),
	MaxEmpircalValue(100),
	EmpiraclValue(MaxEmpircalValue),
	CoolDown(2.f),
	Gold(80),

	AddGold(30),
	AddHealth(0.f),
	AddPhysicalAttack(0.f),
	AddArmor(0.f),
	AddEmpircalValue(20),
	AddAttackSpeed(0.f),
	RestoreHealth(0.2f),

	AddPassiveSkillHealth(0.f),
	AddContinueHealth(0.f),
	AddPassiveSkillPhysicalAttack(0.f),
	AddPassiveSkillArmor(0.f),
	AddPassiveSkillAtteckSpeed(0.f),
	ReducePassiveSkillCDTime(0.45f),
	ConstructionTime(5.f)
{




}

bool FCharacterData::IsValid() const
{
	return CharacterID != INDEX_NONE;
}

void FCharacterData::UpdateHealth()
{
	Health = MaxHealth;
}

