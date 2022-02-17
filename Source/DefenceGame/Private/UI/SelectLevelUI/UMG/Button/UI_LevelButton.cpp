// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SelectLevelUI/UMG/Button/UI_LevelButton.h"
#include <Components/Button.h>
#include <Kismet/GameplayStatics.h>

void UUI_LevelButton::NativeConstruct()
{
	Super::NativeConstruct();

	
	//绑定按钮
	NextLevelButton->OnReleased.AddDynamic(this, &UUI_LevelButton::SelectLevel);

}

void UUI_LevelButton::SelectLevel()
{
	//点击选择地图的时候进行地图切换
	// @param  context  使用的是getworld
	// @param  地图名字
	UGameplayStatics::OpenLevel(GetWorld(), "TestMap");
}
