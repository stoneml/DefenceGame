// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TowerDefenceHallHUD.generated.h"

/**
 * 
 */

class UUI_MainHall;

UCLASS()
class DEFENCEGAME_API ATowerDefenceHallHUD : public AHUD
{
	GENERATED_BODY()
	

public:
	ATowerDefenceHallHUD();


	virtual void BeginPlay() override;

protected:

	//MainHallClass��������׽�ⲿ��ͼ��Դ��
	//������UMG
	//TSubclassOf ���ǿ�������ͼ�н���������д�������ƿ����˱�����Editһ��
	TSubclassOf<UUI_MainHall>MainHallClass;

	//����һ�����˵���UMG
	UUI_MainHall* MainHall;


};
