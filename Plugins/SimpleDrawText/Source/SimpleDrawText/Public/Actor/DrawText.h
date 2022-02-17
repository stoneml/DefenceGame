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

	//Timeline��Upadate����
	UFUNCTION()
	void TimelineRangeTime(float Val);

	//Timeline��finished����
	UFUNCTION()
	void TimelineFinished();

	//����DrawText������
	void SetTextBlock(const FString& InText,const FLinearColor& InColor,float InPercentage);


protected:

	//������ǰTimeline
	FTimeline CurrentTimeline;


private:

	//Timelineʹ�õ�curve
	UPROPERTY(EditDefaultsOnly,Category = Timeline)
	FRuntimeFloatCurve CurveFloatClass;

	//���һ��WidgetComponent
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = BaseAttribute, meta = (AllowPrivateAccess = true))
	class UWidgetComponent* TextWidget;

	//���������ʾ�ĸ߶�
	UPROPERTY(EditAnywhere,Category = DrawText)
	float Height;
	

};
