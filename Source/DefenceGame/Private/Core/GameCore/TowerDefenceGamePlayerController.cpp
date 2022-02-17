// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/GameCore/TowerDefenceGamePlayerController.h"
#include <Core/GameCore/TowerDefenceGameCamera.h>
#include "UI/Core/UI_Datas.h"



ATowerDefenceGamePlayerController::ATowerDefenceGamePlayerController()
{
	//���������ʾ
	bShowMouseCursor = true;

	//Ĭ������Ϊ0
	BeginPlayInt = 0;


}

void ATowerDefenceGamePlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	//����һ���ƶ��ٶȣ�Ȼ��Controller�Լ������ƶ�����
	float ScreenMoveSpeed = 20.f;
	ScreenMoveUnits.ListenScreenMove(this, ScreenMoveSpeed);

	//BeginPlay�޷�ִ�У���ʱʹ��tickִ��һ��BeginPlay
	if (BeginPlayInt ==0)
	{
		BeginPlayInt++;
		//SetInputModeGameAndUI();
	}


	//Tick����������ݼ��
	if (TowerDoll)
	{
			if (MouseTraceHit.Location!= FVector::ZeroVector)
			{
				MouseTraceHit.Location = FVector::ZeroVector;
			}

			//λ�ü��
			FHitResult TempHitResult;
			GetHitResultUnderCursor(ECC_GameTraceChannel4, true, TempHitResult);
			TowerDoll->SetActorLocation(TempHitResult.Location);
	}
	else
	{
		GetHitResultUnderCursor(ECC_WorldStatic, true, MouseTraceHit);

	}


}

void ATowerDefenceGamePlayerController::BeginPlay()
{

	Super::BeginPlay();
	//ִ��beginPlay��ʱ��ֱ�������ӿ�
	//SetInputMode_GameModeGameAndUIEx()
	//�������ͼ����ʹ��SetInputModeAndUI
	SetInputModeGameAndUI();



}

void ATowerDefenceGamePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	//ִ��beginPlay��ʱ��ֱ�������ӿ�
	//SetInputMode_GameModeGameAndUIEx()
	//�������ͼ����ʹ��SetInputModeAndUI
	//SetInputModeGameAndUI();

}

//������������ӿ�
void ATowerDefenceGamePlayerController::SetInputModeGameAndUI()
{
	//��Ҫ�������ݽṹ
	FInputModeGameAndUI InputMode;
	//���ʼ���������ӿ���
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	//���������ʧ
	InputMode.SetHideCursorDuringCapture(false);

	//��������ģʽ
	SetInputMode(InputMode);

}

void ATowerDefenceGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//��껬��
	//��Action Mappingsʹ��
	//@param �ֱ��ǣ���ӳ������֡�����״̬�����Լ�(ʹ����Use class)����Ӧ���õĺ���
	InputComponent->BindAction("MouseWheelUp", IE_Pressed, this, &ATowerDefenceGamePlayerController::MouseWheelUp);
	InputComponent->BindAction("MouseWheelDown", IE_Pressed, this, &ATowerDefenceGamePlayerController::MouseWheelDown);
	InputComponent->BindAction("MouseMiddleButton", IE_Pressed, this, &ATowerDefenceGamePlayerController::MouseMiddleButtonPressed);
	InputComponent->BindAction("MouseMiddleButton", IE_Released, this, &ATowerDefenceGamePlayerController::MouseMiddleButtonReleased);

}

//���Դ��룬�����Ὣ���ݿ���뵽���ñ���
static float WheelValue = 50;

void ATowerDefenceGamePlayerController::MouseWheelUp()
{
	//�Ȼ�ȡCamera
	ATowerDefenceGameCamera* ZoomCamera = Cast<ATowerDefenceGameCamera>(GetPawn());
	//��ȡ�ɹ������õ���
	if (ZoomCamera)
	{
		ZoomCamera->Zoom(true, WheelValue);
	}

}

void ATowerDefenceGamePlayerController::MouseWheelDown()
{
	ATowerDefenceGameCamera* ZoomCamera = Cast<ATowerDefenceGameCamera>(GetPawn());
	if (ZoomCamera)
	{
		ZoomCamera->Zoom(false, WheelValue);
	}
}

void ATowerDefenceGamePlayerController::MouseMiddleButtonPressed()
{
	//������˰󶨾�ִ��
	EventMouseMiddlePressed.ExecuteIfBound();
}

void ATowerDefenceGamePlayerController::MouseMiddleButtonReleased()
{
	EventMouseMiddleReleased.ExecuteIfBound();
}
