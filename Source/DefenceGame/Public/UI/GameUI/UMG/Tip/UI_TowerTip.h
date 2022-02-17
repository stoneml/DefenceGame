// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Core/UI_RuleOfTheWidget.h"
#include "UI_TowerTip.generated.h"

/**
 * 
 */

class UTextBlock;
class UMultiLineEditableText;

UCLASS()
class DEFENCEGAME_API UUI_TowerTip : public UUI_RuleOfTheWidget
{
	GENERATED_BODY()
	

public:

	//Tip参数列表
	//角色名字
	UPROPERTY(meta = (BindWidget))
		UTextBlock* CharacterNameBlock;

	//消费金额
	UPROPERTY(meta = (BindWidget))
		UTextBlock* ConsumeGoldBlock;

	//角色血量
	UPROPERTY(meta = (BindWidget))
		UTextBlock* CharacterHealthBlock;

	//角色攻击力
	UPROPERTY(meta = (BindWidget))
		UTextBlock* CharacterAttackBlock;

	//角色攻击速度
	UPROPERTY(meta = (BindWidget))
		UTextBlock* CharacterAttackSpeedBlock;

	//角色护甲
	UPROPERTY(meta = (BindWidget))
		UTextBlock* CharacterArmorBlock;

	//介绍
	UPROPERTY(meta = (BindWidget))
		UMultiLineEditableText* IntroductionBox;


public:

	UFUNCTION(BlueprintCallable,BlueprintPure)
	void InitTip(const FCharacterData& InData);

};
