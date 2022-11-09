// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/GameCore/TowerDefenceGameCamera.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <Components/BoxComponent.h>

// Sets default values
ATowerDefenceGameCamera::ATowerDefenceGameCamera()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//在构造函数中使用CreateDefaultSubobject
	//如果在BeginPlay中进行创建的话就是用NewObject
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Boom"));
	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	MarkBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Sign"));

	//将创建好的组件绑定到根组件
	CameraBoom->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	MainCamera->AttachToComponent(CameraBoom, FAttachmentTransformRules::KeepRelativeTransform);
	MarkBox->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);


	//设置吊臂参数
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));   //-60就是正300

	//设置MarkBox的碰撞预设为新设置的ControlPawnProfile
	MarkBox->SetCollisionProfileName(TEXT("ControlPawnProfile"));
// 	MarkBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
// 	MarkBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);  //碰撞通道响应关闭
// 	MarkBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility,ECollisionResponse::ECR_Overlap);
// 	MarkBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic,ECollisionResponse::ECR_Overlap);

	//修改这个就可以将吊臂的碰撞关闭
	CameraBoom->bDoCollisionTest = false;

}


// Called when the game starts or when spawned
void ATowerDefenceGameCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATowerDefenceGameCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATowerDefenceGameCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATowerDefenceGameCamera::Zoom(bool bDirection, const float& ZoomSpeed)
{
	
	//判断方向，到底是想要放大还是缩小
	//变焦速度
	if (bDirection)
	{
		//为真就是向前缩放
		if (CameraBoom->TargetArmLength>=800)
		{
			CameraBoom->TargetArmLength -= ZoomSpeed * 2;
		}
	}
	else
	{
		//为假就是向后缩放
		if (CameraBoom->TargetArmLength<=800)
		{
			CameraBoom->TargetArmLength += ZoomSpeed * 2;
		}
	}

}

