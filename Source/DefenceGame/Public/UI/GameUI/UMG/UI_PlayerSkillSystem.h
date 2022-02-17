// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Core/UI_RuleOfTheWidget.h"
#include "UI_PlayerSkillSystem.generated.h"

/**
 * 
 */


class UUI_SkillSlot;
struct FKey;

UCLASS()
class DEFENCEGAME_API UUI_PlayerSkillSystem : public UUI_RuleOfTheWidget
{
	GENERATED_BODY()

private:

	//需要使用到 UUI_SkillSlot 来制作玩家技能
	//目前有4个Skill，所以需要添加4个按钮

	//冻结技能
	UPROPERTY(meta = (BindWidget))
		UUI_SkillSlot* FreezeSkill;

	//爆炸技能
	UPROPERTY(meta = (BindWidget))
		UUI_SkillSlot* ExplosionSkill;

	//回复技能（回复所有塔80%的血量，根据需要自定义）
	UPROPERTY(meta = (BindWidget))
		UUI_SkillSlot* RecoverySkill;

	//回复主塔(HQ)的血
	UPROPERTY(meta = (BindWidget))
		UUI_SkillSlot* RecoveryMainTowerSkill;

public:

	virtual void NativeConstruct();

private:

	//创建4个FKey，对应上面几个技能
	FKey FreezeSkillKey;
	FKey ExplosionSkillKey;
	FKey RecoverySkillKey;
	FKey RecoveryMainTowerSkillKey;
	
};
