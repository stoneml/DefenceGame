// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/GameCore/TowerDefenceGameInstance.h"
#include <SimpleScreenLoading.h>
#include <Modules/ModuleManager.h>

void UTowerDefenceGameInstance::Init()
{
	Super::Init();

	//在初始化的时候，创建一个模块的类应用。
	FSimpleScreenLoadingModule &SimpleScreenLoadingModule = FModuleManager::LoadModuleChecked<FSimpleScreenLoadingModule>("SimpleScreenLoading");

	//创建完成后进行模块中的函数使用
	//这里调用时必须使用指针箭头才能找到这个函数，但是loadmodulechecked返回的是栈内存的东西。不是指针
	SimpleScreenLoadingModule.SetupScreenLoading();

}
