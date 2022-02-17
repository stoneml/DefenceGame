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

//�ӵ�����
UENUM(BlueprintType)
enum class EBulletType:uint8
{
	BULLET_DIRECT_LINE,		//�ᴩ��
	BULLET_LINE,			//ֱ���ӵ�
	BULLET_TRACK_LINE,		//׷�ٵ�
	BULLET_TRACK_LINE_SP,		//׷�ٵ�
	BULLET_RANGE_LINE,		//�����߶�����
	BULLET_RANGE,			//��Χ�˺�
	BULLET_CHAIN			//��ʽ�ӵ�

};


UENUM(BlueprintType)
enum class ECharacterType: uint8
{
	TOWER,
	MONSTER
};