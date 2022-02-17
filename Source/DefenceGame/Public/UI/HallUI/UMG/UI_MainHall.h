// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Core/UI_RuleOfTheWidget.h"
#include <Components/Button.h>
#include "UI_MainHall.generated.h"

/**
 * 
 */
UCLASS()
class DEFENCEGAME_API UUI_MainHall : public UUI_RuleOfTheWidget
{
	GENERATED_BODY()
	

public:

	//��ʼ��UI
	virtual void NativeConstruct();

	//������ӦButton���ܵĺ���
//Ȼ�󽫺����󶨵�UButton��
//��Ϊ��������Ҫͨ����̬�ಥȥ��ӣ�������Ҫ���UFunction
	UFUNCTION()
		void GameStart();

	UFUNCTION()
		void SecretTerritory();

	UFUNCTION()
		void Histroy();

	UFUNCTION()
		void GameSettings();

	UFUNCTION()
		void TutorialsWebsite();

	UFUNCTION()
		void Brower();

	UFUNCTION()
		void SpecialContent();

	UFUNCTION()
		void QuitGame();


protected:

	//��һ���˵����
	UPROPERTY(meta = (BindWidget))
		class UUI_HallMenuSystem* HallMenuSystem;

	//��UI�е�MainBorder
	UPROPERTY(meta = (BindWidget))
		class UBorder* MainBorder;

	//��UI�е�BoxList
	UPROPERTY(meta = (BindWidget))
		class USizeBox* BoxList;

	//��ӵ������浵��ϵͳ����Ϸ����ϵͳ����ѧϵͳ����
	UPROPERTY(EditDefaultsOnly, Category = UI)
		TSubclassOf<class UUI_ArchivesSystem> AcrchivesSystemClass;
	UPROPERTY(EditDefaultsOnly, Category = UI)
		TSubclassOf<class UUI_GameSettingsSystem> GameSettingsSystemClass;
	UPROPERTY(EditDefaultsOnly, Category = UI)
		TSubclassOf<class UUI_TutorialsWebsite> TutorialsSystemClass;


};
