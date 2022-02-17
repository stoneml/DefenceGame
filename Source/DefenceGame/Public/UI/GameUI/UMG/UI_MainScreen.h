// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Core/UI_RuleOfTheWidget.h"
#include "UI_MainScreen.generated.h"

/**
 * 
 */
UCLASS()
class DEFENCEGAME_API UUI_MainScreen : public UUI_RuleOfTheWidget
{
	GENERATED_BODY()
	

private:

	//��Ӳ˵�UI
	UPROPERTY(meta = (BindWidget))
		class UUI_GameMenuSystem* GameMenuSystem;

	//���InfoPrint��������ӡ��Ҳ����Ĺؼ�����
	UPROPERTY(meta = (BindWidget))
		class UUI_GameInfoPrintSystem* GameInfoPrintSystem;

	//С��ͼϵͳ
	UPROPERTY(meta = (BindWidget))
		class UUI_MiniMapSystem* MiniMapSystem;

	//����ϵͳ
	UPROPERTY(meta = (BindWidget))
		class UUI_MissionSystem* MissionSystem;

	//����ϵͳ
	UPROPERTY(meta = (BindWidget))
		class UUI_PlayerSkillSystem* PlayerSkillSystem;

	//����ϵͳ
	UPROPERTY(meta = (BindWidget))
		class UUI_RucksackSystem* RucksackSystem;

	//������
	UPROPERTY(meta = (BindWidget))
		class UUI_ToolBarSystem* ToolBarSystem;

public:

	virtual void NativeConstruct(); 


private:

	//��ק��ɼ�⣬Ԥ��UI��ק���հ״�ʱ����
	bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);

};
