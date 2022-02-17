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

	//��Ҫʹ�õ� UUI_SkillSlot ��������Ҽ���
	//Ŀǰ��4��Skill��������Ҫ���4����ť

	//���Ἴ��
	UPROPERTY(meta = (BindWidget))
		UUI_SkillSlot* FreezeSkill;

	//��ը����
	UPROPERTY(meta = (BindWidget))
		UUI_SkillSlot* ExplosionSkill;

	//�ظ����ܣ��ظ�������80%��Ѫ����������Ҫ�Զ��壩
	UPROPERTY(meta = (BindWidget))
		UUI_SkillSlot* RecoverySkill;

	//�ظ�����(HQ)��Ѫ
	UPROPERTY(meta = (BindWidget))
		UUI_SkillSlot* RecoveryMainTowerSkill;

public:

	virtual void NativeConstruct();

private:

	//����4��FKey����Ӧ���漸������
	FKey FreezeSkillKey;
	FKey ExplosionSkillKey;
	FKey RecoverySkillKey;
	FKey RecoveryMainTowerSkillKey;
	
};
