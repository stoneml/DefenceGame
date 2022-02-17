// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include <GameFramework/GameMode.h>
#include "DefenceGameGameModeBase.generated.h"

/**
 * 
 */

//让GameMode继承自AGameMode，就能够让BeginPlay有效
UCLASS()
class DEFENCEGAME_API ADefenceGameGameModeBase : public AGameMode
{
	GENERATED_BODY()

public:

	//创建GameMode的构造函数
	ADefenceGameGameModeBase();



};
