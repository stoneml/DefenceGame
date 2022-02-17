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


	//放置对应的角色属性(使用纯虚函数，让继承的子类必须实现)
//是否死亡
	virtual bool IsDeath() = 0;
	//获取生命值
	virtual	float GetHealth() = 0;
	//获取最大生命值
	virtual float GetMaxHealth() = 0;
	//是否是同一队伍
	virtual bool IsTeam() = 0;

	//获取角色数据
	virtual FCharacterData& GetCharacterData() = 0;

	//角色类型的返回函数
	virtual EGameCharacterType::Type GetType() = 0;


};
