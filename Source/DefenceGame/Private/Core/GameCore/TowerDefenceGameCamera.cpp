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

	//�ڹ��캯����ʹ��CreateDefaultSubobject
	//�����BeginPlay�н��д����Ļ�������NewObject
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Boom"));
	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	MarkBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Sign"));

	//�������õ�����󶨵������
	CameraBoom->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	MainCamera->AttachToComponent(CameraBoom, FAttachmentTransformRules::KeepRelativeTransform);
	MarkBox->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);


	//���õ��۲���
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));   //-60������300

	//����MarkBox����ײԤ��Ϊ�����õ�ControlPawnProfile
	MarkBox->SetCollisionProfileName(TEXT("ControlPawnProfile"));

	//�޸�����Ϳ��Խ����۵���ײ�ر�
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
	
	//�жϷ��򣬵�������Ҫ�Ŵ�����С
	//�佹�ٶ�
	if (bDirection)
	{
		//Ϊ�������ǰ����
		if (CameraBoom->TargetArmLength>=800)
		{
			CameraBoom->TargetArmLength -= ZoomSpeed * 2;
		}
	}
	else
	{
		//Ϊ�پ����������
		if (CameraBoom->TargetArmLength<=800)
		{
			CameraBoom->TargetArmLength += ZoomSpeed * 2;
		}
	}

}

