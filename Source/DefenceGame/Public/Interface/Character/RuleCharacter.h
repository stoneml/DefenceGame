// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include <../DefenceGameType.h>
#include "Data/Core/CharacterData.h"
#include "RuleCharacter.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class URuleCharacter : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DEFENCEGAME_API IRuleCharacter
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:


	//���ö�Ӧ�Ľ�ɫ����(ʹ�ô��麯�����ü̳е��������ʵ��)
//�Ƿ�����
	virtual bool IsDeath() = 0;
	//��ȡ����ֵ
	virtual	float GetHealth() = 0;
	//��ȡ�������ֵ
	virtual float GetMaxHealth() = 0;
	//�Ƿ���ͬһ����
	virtual bool IsTeam() = 0;

	//��ȡ��ɫ����
	virtual FCharacterData& GetCharacterData() = 0;

	//��ɫ���͵ķ��غ���
	virtual EGameCharacterType::Type GetType() = 0;


};
