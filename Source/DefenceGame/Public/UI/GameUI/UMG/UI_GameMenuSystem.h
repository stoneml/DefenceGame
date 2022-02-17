// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Core/UI_RuleOfTheWidget.h"
#include "UI_GameMenuSystem.generated.h"

/**
 * 
 */

class UButton;

UCLASS()
class DEFENCEGAME_API UUI_GameMenuSystem : public UUI_RuleOfTheWidget
{
	GENERATED_BODY()
	
private:

	//������Ϸ��ť
	UPROPERTY(meta = (BindWidget))
		UButton* ReturnGameButton;

	//������Ϸ��ť
	UPROPERTY(meta = (BindWidget))
		UButton* SaveGameButton;

	//��Ϸ���ð�ť
	UPROPERTY(meta = (BindWidget))
		UButton* GameSettingButton;

	//��Ϸ�˳���ť
	UPROPERTY(meta = (BindWidget))
		UButton* GameQuitButton;



public:

	//��ʼ��UI
	virtual void NativeConstruct();


private:
	//������Ӧ�ĺ���
	//��Ϊ�󶨵��Ƕ�̬�ಥ��������Ҫ���UFUNCTION
	UFUNCTION()
		void ReturnGame();
	UFUNCTION()
		void SaveGame();
	UFUNCTION()
		void GameSetting();
	UFUNCTION()
		void GameQuit();



};
