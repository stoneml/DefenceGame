// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/GameCore/TowerDefenceGamePlayerController.h"
#include <Core/GameCore/TowerDefenceGameCamera.h>
#include "UI/Core/UI_Datas.h"



ATowerDefenceGamePlayerController::ATowerDefenceGamePlayerController()
{
	//开启鼠标显示
	bShowMouseCursor = true;

	//默认设置为0
	BeginPlayInt = 0;


}

void ATowerDefenceGamePlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	//定义一个移动速度，然后将Controller自己传给移动监听
	float ScreenMoveSpeed = 20.f;
	ScreenMoveUnits.ListenScreenMove(this, ScreenMoveSpeed);

	//BeginPlay无法执行，暂时使用tick执行一次BeginPlay
	if (BeginPlayInt ==0)
	{
		BeginPlayInt++;
		//SetInputModeGameAndUI();
	}


	//Tick进行鼠标内容检测
	if (TowerDoll)
	{
			if (MouseTraceHit.Location!= FVector::ZeroVector)
			{
				MouseTraceHit.Location = FVector::ZeroVector;
			}

			//位置检测
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
	//执行beginPlay的时候，直接锁定视口
	//SetInputMode_GameModeGameAndUIEx()
	//如果是蓝图可以使用SetInputModeAndUI
	SetInputModeGameAndUI();



}

void ATowerDefenceGamePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	//执行beginPlay的时候，直接锁定视口
	//SetInputMode_GameModeGameAndUIEx()
	//如果是蓝图可以使用SetInputModeAndUI
	//SetInputModeGameAndUI();

}

//将鼠标锁定与视口
void ATowerDefenceGamePlayerController::SetInputModeGameAndUI()
{
	//需要输入数据结构
	FInputModeGameAndUI InputMode;
	//鼠标始终锁定在视口内
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	//鼠标点击不消失
	InputMode.SetHideCursorDuringCapture(false);

	//设置输入模式
	SetInputMode(InputMode);

}

void ATowerDefenceGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//鼠标滑轮
	//绑定Action Mappings使用
	//@param 分别是，绑定映射的名字、按下状态、绑定自己(使用者Use class)、对应调用的函数
	InputComponent->BindAction("MouseWheelUp", IE_Pressed, this, &ATowerDefenceGamePlayerController::MouseWheelUp);
	InputComponent->BindAction("MouseWheelDown", IE_Pressed, this, &ATowerDefenceGamePlayerController::MouseWheelDown);
	InputComponent->BindAction("MouseMiddleButton", IE_Pressed, this, &ATowerDefenceGamePlayerController::MouseMiddleButtonPressed);
	InputComponent->BindAction("MouseMiddleButton", IE_Released, this, &ATowerDefenceGamePlayerController::MouseMiddleButtonReleased);

}

//测试代码，后续会将数据库加入到配置表中
static float WheelValue = 50;

void ATowerDefenceGamePlayerController::MouseWheelUp()
{
	//先获取Camera
	ATowerDefenceGameCamera* ZoomCamera = Cast<ATowerDefenceGameCamera>(GetPawn());
	//获取成功后设置吊臂
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
	//如果有人绑定就执行
	EventMouseMiddlePressed.ExecuteIfBound();
}

void ATowerDefenceGamePlayerController::MouseMiddleButtonReleased()
{
	EventMouseMiddleReleased.ExecuteIfBound();
}
