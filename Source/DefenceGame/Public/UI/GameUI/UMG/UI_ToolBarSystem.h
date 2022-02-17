// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Core/UI_RuleOfTheWidget.h"
#include "UI_ToolBarSystem.generated.h"

/**
 * 
 */

class UTextBlock;
class UProgressBar;

UCLASS()
class DEFENCEGAME_API UUI_ToolBarSystem : public UUI_RuleOfTheWidget
{
	GENERATED_BODY()
	

private:
	//��Ϸ�������
	UPROPERTY(meta = (BindWidget))
		UTextBlock* GameGold;
	//�ҷ�����������
	UPROPERTY(meta = (BindWidget))
		UTextBlock* TowerDeathNumber;
	//��Ϸʱ��
	UPROPERTY(meta = (BindWidget))
		UTextBlock* GameCount;
	//��ɱ����
	UPROPERTY(meta = (BindWidget))
		UTextBlock* KillSolider;

	//��ʾʣ��������� (Surplus:ʣ��) ��Quantity������)
	UPROPERTY(meta = (BindWidget))
		UTextBlock* GameLevelSurplusQuantity;

	//��ɻ�ɱ������
	UPROPERTY(meta = (BindWidget))
		UProgressBar* GSQProgressBar;

public:

	virtual void NativeConstruct();


};
