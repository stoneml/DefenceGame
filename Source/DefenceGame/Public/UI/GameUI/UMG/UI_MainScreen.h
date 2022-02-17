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

	//添加菜单UI
	UPROPERTY(meta = (BindWidget))
		class UUI_GameMenuSystem* GameMenuSystem;

	//添加InfoPrint，用来打印玩家操作的关键步骤
	UPROPERTY(meta = (BindWidget))
		class UUI_GameInfoPrintSystem* GameInfoPrintSystem;

	//小地图系统
	UPROPERTY(meta = (BindWidget))
		class UUI_MiniMapSystem* MiniMapSystem;

	//任务系统
	UPROPERTY(meta = (BindWidget))
		class UUI_MissionSystem* MissionSystem;

	//技能系统
	UPROPERTY(meta = (BindWidget))
		class UUI_PlayerSkillSystem* PlayerSkillSystem;

	//背包系统
	UPROPERTY(meta = (BindWidget))
		class UUI_RucksackSystem* RucksackSystem;

	//工具栏
	UPROPERTY(meta = (BindWidget))
		class UUI_ToolBarSystem* ToolBarSystem;

public:

	virtual void NativeConstruct(); 


private:

	//拖拽完成检测，预防UI拖拽到空白处时销毁
	bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);

};
