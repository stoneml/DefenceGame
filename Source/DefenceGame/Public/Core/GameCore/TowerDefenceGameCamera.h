// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TowerDefenceGameCamera.generated.h"

UCLASS()
class DEFENCEGAME_API ATowerDefenceGameCamera : public APawn
{
	GENERATED_BODY()


public:
	// Sets default values for this pawn's properties
	ATowerDefenceGameCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:

	//变量声明

	//当出现这样的报错时，LogCompile: Error: BlueprintReadOnly should not be used on private members
	//添加meta =(AllowPrivateAccess = "true")

	//控制相机距离
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	//主相机
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* MainCamera;

	//摄像机的碰撞表示
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* MarkBox;


public:

	//用来做缩放聚焦的函数
	void Zoom(bool bDirection, const float& ZoomSpeed);


};
