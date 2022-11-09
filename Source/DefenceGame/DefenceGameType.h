// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DefenceGameType.generated.h"



UENUM()
namespace EGameCharacterType
{
	enum Type
	{
		TOWER,
		MAIN_TOWER,
		MONSTER,
		BOSS_MONSTER,
		MAX
	};
}

//子弹类型
UENUM(BlueprintType)
enum class EBulletType:uint8
{
	BULLET_DIRECT_LINE,		//贯穿弹
	BULLET_LINE,			//直线子弹
	BULLET_TRACK_LINE,		//追踪弹
	BULLET_TRACK_LINE_SP,		//追踪弹
	BULLET_RANGE_LINE,		//抛物线丢手雷
	BULLET_RANGE,			//范围伤害
	BULLET_CHAIN			//链式子弹

};


UENUM(BlueprintType)
enum class ECharacterType: uint8
{
	TOWER,
	MONSTER
};
 