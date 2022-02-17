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

	//Tip�����б�
	//��ɫ����
	UPROPERTY(meta = (BindWidget))
		UTextBlock* CharacterNameBlock;

	//���ѽ��
	UPROPERTY(meta = (BindWidget))
		UTextBlock* ConsumeGoldBlock;

	//��ɫѪ��
	UPROPERTY(meta = (BindWidget))
		UTextBlock* CharacterHealthBlock;

	//��ɫ������
	UPROPERTY(meta = (BindWidget))
		UTextBlock* CharacterAttackBlock;

	//��ɫ�����ٶ�
	UPROPERTY(meta = (BindWidget))
		UTextBlock* CharacterAttackSpeedBlock;

	//��ɫ����
	UPROPERTY(meta = (BindWidget))
		UTextBlock* CharacterArmorBlock;

	//����
	UPROPERTY(meta = (BindWidget))
		UMultiLineEditableText* IntroductionBox;


public:

	UFUNCTION(BlueprintCallable,BlueprintPure)
	void InitTip(const FCharacterData& InData);

};
