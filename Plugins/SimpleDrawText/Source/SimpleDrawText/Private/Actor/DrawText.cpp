// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/DrawText.h"
#include "Components/WidgetComponent.h"
#include "UI/UI_InformationWidget.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
ADrawText::ADrawText()
	:Height(0.f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	

	TextWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("TextWidget"));
	TextWidget->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned
void ADrawText::BeginPlay()
{
	Super::BeginPlay();
	
	//���ж�һ���������Ƿ��ж��������ʵ��
	if (CurveFloatClass.ExternalCurve)
	{
/*
		/ ** Signature of function to handle a timeline 'event' * /
		DECLARE_DYNAMIC_DELEGATE(FOnTimelineEvent);
		/ ** Signature of function to handle timeline float track * /
		DECLARE_DYNAMIC_DELEGATE_OneParam(FOnTimelineFloat, float, Output);*/

/*
		��1�� ����TimelineFloatDel��FinishedEvent����֪ͨ
		��2�� ��������֪ͨ�󶨶�Ӧ�ĺ���TimelineRangeTime��TimelineFinished
		��3�� ��Timeline������ߺͶ�Ӧ��Update������ʱ�����Ӵ����ֵ��
		��4�� ����ѭ����������false��
		��5�� ����PlayFromStart
		��6�� ����TimelineFinishedFunc��FinishedEvent��, �ص�����
		��7�� Tick��ǰ��Timeline��*/


		FOnTimelineEvent TimelineFinished;
		FOnTimelineFloat TimelineFloatDel;

		TimelineFloatDel.BindUFunction(this,FName("TimelineRangeTime"));
		TimelineFinished.BindUFunction(this,FName("TimelineFinished"));

		CurrentTimeline.AddInterpFloat(CurveFloatClass.ExternalCurve, TimelineFloatDel);
		CurrentTimeline.SetLooping(false);
		CurrentTimeline.PlayFromStart();
		CurrentTimeline.SetTimelineFinishedFunc(TimelineFinished);

	}



}

// Called every frame
void ADrawText::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Tick��ǰ��Timeline��
	if (CurveFloatClass.ExternalCurve)
	{
		CurrentTimeline.TickTimeline(DeltaTime);
	}

}

void ADrawText::TimelineRangeTime(float Val)
{
	//ͨ��Lerp�����в�ֵ�仯��
	if (Height>0)
	{
		FVector NewHeight = UKismetMathLibrary::VLerp(FVector::ZeroVector, FVector(0, 0, Height), Val);
		//��������Ʈ��ֵ
		TextWidget->AddRelativeLocation(NewHeight);
	}
}

void ADrawText::TimelineFinished()
{
	//��ɶ����������Լ�
	Destroy(true);
}

void ADrawText::SetTextBlock(const FString& InText, const FLinearColor& InColor, float InPercentage)
{
	//����ֵ��Widget
	if (UUI_InformationWidget* InfoWidget = Cast<UUI_InformationWidget>(TextWidget->GetUserWidgetObject()))
	{
		InfoWidget->SetTextBlockStyle(InText, InColor, InPercentage);
	}
}

