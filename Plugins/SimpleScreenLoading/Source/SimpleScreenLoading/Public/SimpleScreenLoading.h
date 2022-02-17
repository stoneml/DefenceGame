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


	//��GameInstance��ʵ�֣�GI������Ϊ�ؿ��л�����������
	SIMPLESCREENLOADING_API void SetupScreenLoading();

private:

	//���ض�ȡ
	void BeginLoadingScreen(const FString& MapName);

	//�������ʱ֪ͨ�ر�
	void EndLoadingScreen(UWorld* World);
};
