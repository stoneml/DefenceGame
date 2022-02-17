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

	//按下鼠标代理
	FSimpleDelegate EventMouseMiddlePressed;

	//松开鼠标代理
	FSimpleDelegate EventMouseMiddleReleased;



public:
	//PlayerController的构造函数
	ATowerDefenceGamePlayerController();

	//Tick调用
	virtual void Tick(float DeltaSeconds) override;


	//初始化操作
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn)override;

	//锁定鼠标
	void SetInputModeGameAndUI();



	//运行玩家自己更新自己的绑定响应
	virtual void SetupInputComponent()override;

	//鼠标滚轮事件
	//这两个函数是用来在进行映射绑定时候使用到的
	void MouseWheelUp();
	void MouseWheelDown();


	//鼠标控制函数
	void MouseMiddleButtonPressed();
	void MouseMiddleButtonReleased();

protected:

	//创建一个移动单元
	FScreenMoveUnits ScreenMoveUnits;


	//保存点击数据
	FHitResult MouseTraceHit;

	int32 BeginPlayInt;

};
