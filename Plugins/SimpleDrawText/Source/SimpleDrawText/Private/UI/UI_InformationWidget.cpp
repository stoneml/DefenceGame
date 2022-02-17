// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UI_InformationWidget.h"
#include "Components/TextBlock.h"

void UUI_InformationWidget::SetTextBlockStyle(const FString& InText, const FLinearColor& InColor, float InPercentage)
{
	//计算字体大小
	int32 MaxSize = 50;
	int32 MinSize = 16;
	int32 CurrentSize = MinSize + (MaxSize - MinSize) * InPercentage;

	//设置字体信息
	//TextWidget->Font.Size = CurrentSize;
	TextWidget->SetText(FText::FromString(InText));
	TextWidget->SetColorAndOpacity(InColor);

}
