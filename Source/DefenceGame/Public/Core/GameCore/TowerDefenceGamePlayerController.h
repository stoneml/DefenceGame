// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Tool/ScreenMove.h"
#include "TowerDefenceGamePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DEFENCEGAME_API ATowerDefenceGamePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	//����������
	FSimpleDelegate EventMouseMiddlePressed;

	//�ɿ�������
	FSimpleDelegate EventMouseMiddleReleased;



public:
	//PlayerController�Ĺ��캯��
	ATowerDefenceGamePlayerController();

	//Tick����
	virtual void Tick(float DeltaSeconds) override;


	//��ʼ������
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn)override;

	//�������
	void SetInputModeGameAndUI();



	//��������Լ������Լ��İ���Ӧ
	virtual void SetupInputComponent()override;

	//�������¼�
	//�����������������ڽ���ӳ���ʱ��ʹ�õ���
	void MouseWheelUp();
	void MouseWheelDown();


	//�����ƺ���
	void MouseMiddleButtonPressed();
	void MouseMiddleButtonReleased();

protected:

	//����һ���ƶ���Ԫ
	FScreenMoveUnits ScreenMoveUnits;


	//����������
	FHitResult MouseTraceHit;

	int32 BeginPlayInt;

};
