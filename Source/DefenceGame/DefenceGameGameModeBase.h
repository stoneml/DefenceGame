// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include <GameFramework/GameMode.h>
#include "DefenceGameGameModeBase.generated.h"

/**
 * 
 */

//��GameMode�̳���AGameMode�����ܹ���BeginPlay��Ч
UCLASS()
class DEFENCEGAME_API ADefenceGameGameModeBase : public AGameMode
{
	GENERATED_BODY()

public:

	//����GameMode�Ĺ��캯��
	ADefenceGameGameModeBase();



};
