// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Core/UI_RuleOfTheWidget.h"
#include <Components/Button.h>
#include "UI_HallMenuSystem.generated.h"

/**
 * 
 */

//�˵�UI

//������ť��
class UButton;


UCLASS()
class DEFENCEGAME_API UUI_HallMenuSystem : public UUI_RuleOfTheWidget
{
	GENERATED_BODY()
	


protected:

	//��ʼ��Ϸ��ť
	UPROPERTY(meta = (BindWidget))
		UButton* GameStartButton;

	//����ؾ���ť
	UPROPERTY(meta = (BindWidget))
		UButton* SecretTerritoryButton;

	//����������Ϸ���ߴ�����Ϸ��
	UPROPERTY(meta = (BindWidget))
		UButton* HistoryButton;

	//��Ϸ���ð�ť
	UPROPERTY(meta = (BindWidget))
		UButton* GameSettingsButton;

	//����Ƶ��ť
	UPROPERTY(meta = (BindWidget))
		UButton* TutorialWebsiteButton;

	//�������ť������վ��
	UPROPERTY(meta = (BindWidget))
		UButton* BrowerButton;

	//�ر�����Ҳ����DLC
	UPROPERTY(meta = (BindWidget))
		UButton* SpecialContentButton;

	//�˳���Ϸ
	UPROPERTY(meta = (BindWidget))
		UButton* QuitGameButton;


public:

	//��ʼ����ť = BrginPlay
	virtual void NativeConstruct();


	//������Ӧ�����İ󶨽ӿڣ��󶨸���ĺ���
	void BindGameStart(FOnButtonReleasedEvent ReleaseEvent);
	void BindSecretTerritory(FOnButtonReleasedEvent ReleaseEvent);
	void BindHistory(FOnButtonReleasedEvent ReleaseEvent);
	void BindGameSettings(FOnButtonReleasedEvent ReleaseEvent);
	void BindTutorialWebsite(FOnButtonReleasedEvent ReleaseEvent);
	void BindBrower(FOnButtonReleasedEvent ReleaseEvent);
	void BindSpecialContent(FOnButtonReleasedEvent ReleaseEvent);
	void BindQuitGame(FOnButtonReleasedEvent ReleaseEvent);



};
