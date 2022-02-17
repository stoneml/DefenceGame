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
	
	//先判断一下曲线类是否有而外的曲线实例
	if (CurveFloatClass.ExternalCurve)
	{
/*
		/ ** Signature of function to handle a timeline 'event' * /
		DECLARE_DYNAMIC_DELEGATE(FOnTimelineEvent);
		/ ** Signature of function to handle timeline float track * /
		DECLARE_DYNAMIC_DELEGATE_OneParam(FOnTimelineFloat, float, Output);*/

/*
		（1） 声明TimelineFloatDel和FinishedEvent两个通知
		（2） 给声明的通知绑定对应的函数TimelineRangeTime和TimelineFinished
		（3） 给Timeline添加曲线和对应的Update代理。给时间点添加代理插值。
		（4） 设置循环（这里是false）
		（5） 设置PlayFromStart
		（6） 设置TimelineFinishedFunc（FinishedEvent）, 回调函数
		（7） Tick当前的Timeline。*/


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

	//Tick当前的Timeline。
	if (CurveFloatClass.ExternalCurve)
	{
		CurrentTimeline.TickTimeline(DeltaTime);
	}

}

void ADrawText::TimelineRangeTime(float Val)
{
	//通过Lerp来进行插值变化。
	if (Height>0)
	{
		FVector NewHeight = UKismetMathLibrary::VLerp(FVector::ZeroVector, FVector(0, 0, Height), Val);
		//传递向上飘的值
		TextWidget->AddRelativeLocation(NewHeight);
	}
}

void ADrawText::TimelineFinished()
{
	//完成动画后销毁自己
	Destroy(true);
}

void ADrawText::SetTextBlock(const FString& InText, const FLinearColor& InColor, float InPercentage)
{
	//传递值给Widget
	if (UUI_InformationWidget* InfoWidget = Cast<UUI_InformationWidget>(TextWidget->GetUserWidgetObject()))
	{
		InfoWidget->SetTextBlockStyle(InText, InColor, InPercentage);
	}
}

