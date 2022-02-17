// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FSimpleScreenLoadingModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;


	//在GameInstance中实现，GI不会因为关卡切换而销毁数据
	SIMPLESCREENLOADING_API void SetupScreenLoading();

private:

	//加载读取
	void BeginLoadingScreen(const FString& MapName);

	//加载完成时通知关闭
	void EndLoadingScreen(UWorld* World);
};
