// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "Curves/CurveFloat.h"
#include "DrawText.generated.h"

UCLASS()
class SIMPLEDRAWTEXT_API ADrawText : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADrawText();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:

	//Timeline的Upadate函数
	UFUNCTION()
	void TimelineRangeTime(float Val);

	//Timeline的finished函数
	UFUNCTION()
	void TimelineFinished();

	//设置DrawText的内容
	void SetTextBlock(const FString& InText,const FLinearColor& InColor,float InPercentage);


protected:

	//创建当前Timeline
	FTimeline CurrentTimeline;


private:

	//Timeline使用的curve
	UPROPERTY(EditDefaultsOnly,Category = Timeline)
	FRuntimeFloatCurve CurveFloatClass;

	//添加一个WidgetComponent
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = BaseAttribute, meta = (AllowPrivateAccess = true))
	class UWidgetComponent* TextWidget;

	//添加文字显示的高度
	UPROPERTY(EditAnywhere,Category = DrawText)
	float Height;
	

};
