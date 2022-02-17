// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TowerDefenceSelectLevelHUD.generated.h"

/**
 * 
 */

class UUI_MainSelectLevel;

UCLASS()
class DEFENCEGAME_API ATowerDefenceSelectLevelHUD : public AHUD
{
	GENERATED_BODY()


public:
	//���HUD�еĶ���

	ATowerDefenceSelectLevelHUD();

	virtual void BeginPlay() override;


private:

	//��ȡ��Ӧ��Actor���а�
	//�����ǻ�ȡ�����UI����
	TSubclassOf<UUI_MainSelectLevel>MainSelectLevelClass;

	//����ͨ����ȡ��UI����Ȼ�����UI��ֵ
	UUI_MainSelectLevel* MainSelectLevel;

};
