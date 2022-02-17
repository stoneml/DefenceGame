// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Core/UI_Slot.h"
#include "UI_InventorySlot.generated.h"

/**
 * 
 */

class UImage;
class UButton;
class UTextBlock;

UCLASS()
class DEFENCEGAME_API UUI_InventorySlot : public UUI_Slot
{
	GENERATED_BODY()
	

private:

	//塔图标
	UPROPERTY(meta = (BindWidget))
		UImage* TowerIcon;

	//塔CD蒙版图片
	UPROPERTY(meta = (BindWidget))
		UImage* TowerCD;

	//塔建造数量
	//Tower Prepare Building Number
	UPROPERTY(meta = (BindWidget))
		UTextBlock* TPBNumber;

	//塔建造完成数量
	//Tower Completion Of Construction Number
	UPROPERTY(meta = (BindWidget))
		UTextBlock* TCOCNumber;

	//塔建造CD
	UPROPERTY(meta = (BindWidget))
		UTextBlock* TowerCDValue;

	//按键点击（不仅可以按键盘还可以点击鼠标使用）
	//Tower Inverntory Slot Button
	UPROPERTY(meta = (BindWidget))
		UButton* TISButton;


	//绘制塔CD的相关参数,这两个名字将会是材质的节点参数名称
	UPROPERTY(EditDefaultsOnly,Category = UI)
	FName TowersMatCDName;

	UPROPERTY(EditDefaultsOnly,Category = UI)
	FName TowersClearValueName;


/*
	//暂时用不到的拖拽
	UPROPERTY(EditDefaultsOnly,Category = UI)
	TSubclassOf<class UDefenceDragDropOperation> IcoDragDrop;*/

	//放入UITip
	UPROPERTY(EditDefaultsOnly,Category = Tip)
	TSubclassOf<class UUI_TowerTip> TipUIClass;

	//创建一个拖拽UI
	UPROPERTY(EditDefaultsOnly,Category = UI)
	TSubclassOf<class UUI_ICODragDrop> IconDragUIClass;

	//CD的动态材质
	UPROPERTY()
	class UMaterialInstanceDynamic* CDMaterialDynamic;




	//测试代码（拖拽更新相关）
	int32 ForceUpdateUITime = 50;


public:

	virtual void NativeConstruct();

	//使用Tick来进行数据的刷新
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	//点击事件函数
	UFUNCTION()
		void OnReleasedWidget();

	//更新当前UI信息
	void UpdateUI();

	//获取当前塔信息
	FBuildingTower& GetBuildingTower();

	//创建一个隐藏所有Slot信息的函数
	void ClearSlot();


	//将TipUI暴露给蓝图
	UFUNCTION(BlueprintCallable,BlueprintPure,Category = Tip)
	UWidget* GetTowerTip();

private:
	//创建内部执行接口

	void UpdateTowersCD(float InDataTime);
	void DrawTowersCD(float InTowerCD);
	void DisplayNumber(UTextBlock* TextNumberBlock, int32 TextNumber);
	void UpdateTowersBuildingInfo();


protected:

	//鼠标拖拽事件相关函数
	//鼠标点击
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	//鼠标拖拽检测
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation);
	//鼠标拖拽释放
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);
	//鼠标进入
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	//鼠标离开
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent);


};
