// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameUI/UMG/Inventory/UI_InventorySlot.h"
#include "UI/Core/UI_Datas.h"
#include <Components/Button.h>
#include "Data/Save/GameSaveData.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Input/Reply.h"
#include "Blueprint/DragDropOperation.h"
#include "DragDrop/DefenceDragDropOperation.h"
#include "UI/GameUI/UMG/Inventory/DragDrop/UI_ICODragDrop.h"
#include "UI/GameUI/UMG/Tip/UI_TowerTip.h"
#include "Data/Core/CharacterData.h"


void UUI_InventorySlot::NativeConstruct()
{
	Super::NativeConstruct();

	//绑定按钮
	TISButton->OnReleased.AddDynamic(this, &UUI_InventorySlot::OnReleasedWidget);

	//如果CD图片存在
	if (TowerCD)
	{
		CDMaterialDynamic = TowerCD->GetDynamicMaterial();
	}

	
}

void UUI_InventorySlot::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	//如果没有在暂停状态，就进行刷新
	if (GetBuildingTower().IsValid())
	{
		if (!GetBuildingTower().bLockCD)
		{
			//是否在拖拽
			if (!GetBuildingTower().bDragICO)
			{
				//更新当前CD
				UpdateTowersCD(InDeltaTime);
			}
		}
	}


	if (ForceUpdateUITime<50)
	{
		UpdateUI();
		ForceUpdateUITime++;
	}


}

void UUI_InventorySlot::OnReleasedWidget()
{

// 	● 点击时先要判断当前BuildingTowers是否有意义。
// 	● 然后判断当前金币数量满足购买tower的needgold。（这里暂时设置为1）
// 	● 然后针对塔准备数量进行++（TowersPerpareBuildingNumber）
// 	● 再判断当前的建造CD是 <= 0
// 	● 如果是就要reset当前CD

	if (GetBuildingTower().IsValid())
	{
		if (/*GetBuildingTower().NeedGold*/ 1)
		{
			//开始进行建造排队
			GetBuildingTower().TowersPerpareBuildingNumber++;
			if (GetBuildingTower().CurrentConstrictionTowersCD<=0)
			{
				GetBuildingTower().ResetCD();
			}
		}
	}

	UpdateUI();
}

void UUI_InventorySlot::UpdateUI()
{

	//判断图片是否有效
	if (GetBuildingTower().Icon)
	{
		//如果有效就进行图片的添加
		TowerIcon->SetBrushFromSoftTexture(GetBuildingTower().Icon);
		TowerIcon->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else
	{
		TowerIcon->SetVisibility(ESlateVisibility::Hidden);
	}

	//对当前移动后的UI进行显示判定
	if (GetBuildingTower().TowersConstructionNumber> 0)
	{
		TCOCNumber->SetVisibility(ESlateVisibility::HitTestInvisible);
	}

	if (GetBuildingTower().TowersPerpareBuildingNumber> 0)
	{
		TPBNumber->SetVisibility(ESlateVisibility::HitTestInvisible);
	}


}


FBuildingTower& UUI_InventorySlot::GetBuildingTower()
{
	//从父类获取到当前的GameState
	return GetGameState()->GetBuildingTower(CurrentGUID);

}

void UUI_InventorySlot::ClearSlot()
{
	//TowerIcon->SetVisibility(ESlateVisibility::Hidden);
	TowerCD->SetVisibility(ESlateVisibility::Hidden);
	TPBNumber->SetVisibility(ESlateVisibility::Hidden);
	TCOCNumber->SetVisibility(ESlateVisibility::Hidden);
	TowerCDValue->SetVisibility(ESlateVisibility::Hidden);
}

UWidget* UUI_InventorySlot::GetTowerTip()
{
	if (TipUIClass)
	{
		const FCharacterData& TempData = GetGameState()->GetCharacterDataByID(GetBuildingTower().TowerID);

		//判断一下数据是否是有效的
		if (TempData.IsValid())
		{
			//如果有效那么就开始生成对应UI
			if (UUI_TowerTip* TipUI = CreateWidget<UUI_TowerTip>(GetWorld(), TipUIClass))
			{
				TipUI->InitTip(TempData);
				return TipUI;
			}
		}
	}

	//没有获取到就返回空
	return nullptr;
}

void UUI_InventorySlot::UpdateTowersCD(float InDataTime)
{
	//如果当前建造的塔CD大于0，也就是有塔正在建造
	if (GetBuildingTower().CurrentConstrictionTowersCD>0)
	{
		//绘制CD材质
		DrawTowersCD(GetBuildingTower().GetTowerConstructionTimePercentage());
		//CD递减
		GetBuildingTower().CurrentConstrictionTowersCD -= InDataTime;
		//调用数据更新
		GetBuildingTower().bCallUpdateTowerInfo = true;
		//更新信息
		UpdateTowersBuildingInfo();
	}
	else if (GetBuildingTower().bCallUpdateTowerInfo)
	{
		GetBuildingTower().bCallUpdateTowerInfo = false;
		//准备创建的塔
		//创建完成
		GetBuildingTower().TowersPerpareBuildingNumber--;

		//创建好的+1
		GetBuildingTower().TowersConstructionNumber++; 

		//塔CD绘制完成
		DrawTowersCD(0.0f);

		//如果准备创建的塔的数量大于0，那么就重置CD

		if (GetBuildingTower().TowersPerpareBuildingNumber>0)
		{
			GetBuildingTower().ResetCD();
		}
		//更新塔信息
		UpdateTowersBuildingInfo();
	}
}

void UUI_InventorySlot::DrawTowersCD(float InTowerCD)
{
	if (CDMaterialDynamic)
	{
		if (InTowerCD > 0.f && InTowerCD < 1.f)
		{
			CDMaterialDynamic->SetScalarParameterValue(TowersClearValueName, true);
			//开始倒计时的时候显示
			TowerCD->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		}
		else
		{
			CDMaterialDynamic->SetScalarParameterValue(TowersClearValueName, false);
			TowerCD->SetVisibility(ESlateVisibility::Hidden);
		}

		CDMaterialDynamic->SetScalarParameterValue(TowersMatCDName, InTowerCD);
	}
}

void UUI_InventorySlot::DisplayNumber(UTextBlock* TextNumberBlock, int32 TextNumber)
{
	if (TextNumber < 1 || !GetBuildingTower().IsValid())
	{
		TextNumberBlock->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		//%02d 是为了让数字以 00 ， 01 ，02的形式显示
		TextNumberBlock->SetText(FText::FromString(FString::Printf(TEXT("%02d"), TextNumber)));
		TextNumberBlock->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
}

void UUI_InventorySlot::UpdateTowersBuildingInfo()
{
// 		● 显示塔CD
// 		● 构建完成的数量
// 		● 正在准备创建的塔的数量

	DisplayNumber(TowerCDValue, GetBuildingTower().CurrentConstrictionTowersCD);
	DisplayNumber(TCOCNumber, GetBuildingTower().TowersConstructionNumber);
	DisplayNumber(TPBNumber, GetBuildingTower().TowersPerpareBuildingNumber);
}

FReply UUI_InventorySlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	//判断是否是鼠标右键点击或者是触控事件（触屏）
	if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton || InMouseEvent.IsTouchEvent())
	{
		//创建一个处理响应
		FReply Reply = FReply::Handled();
		//创建一个共享指针，保存SWidget的一个缓存
		TSharedPtr<SWidget>SlateWidgetDrag = GetCachedWidget();

		if (SlateWidgetDrag.IsValid())
		{
			//如果满足缓存有效，那么就提示侦测到拖拽事件，之后会激活NativeOnDragDetected
			//这里需要将共享指针转为共享引用。
			Reply.DetectDrag(SlateWidgetDrag.ToSharedRef(), EKeys::RightMouseButton);
			return Reply;
		}
	}
	return FReply::Handled();
}

void UUI_InventorySlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	//首先获取当前Slot的塔信息
	if (GetBuildingTower().IsValid() && IconDragUIClass)
	{
		//创建一个DragUI
		if (UUI_ICODragDrop* DragUIWidget = CreateWidget<UUI_ICODragDrop>(GetWorld(), IconDragUIClass))
		{
			//创建一个拖拽事件
			if (UDefenceDragDropOperation* DefenceDragOp = NewObject<UDefenceDragDropOperation>(GetTransientPackage(), UDefenceDragDropOperation::StaticClass()))
			{
				//GetTransientPackage() 
				//标记为强引用，不会轻易被回收
				DefenceDragOp->SetFlags(RF_StrongRefOnFrame);
				//设置图标
				DragUIWidget->SetDrawICON(GetBuildingTower().Icon);  //传值后UI的Icon是空的
				//将自己赋值给一个虚幻图标，在拖拽是显示一个一模一样的自己
				//DefenceDragOp->DefaultDragVisual = DefenceDragOp;  这段代码有问题
				DefenceDragOp->DefaultDragVisual = this;
				//在物体移动到另外一个格子的时候进行PayLoad；
				DefenceDragOp->Payload = this;
				//返回拖拽响应事件
				OutOperation = DefenceDragOp;

				GetBuildingTower().bDragICO = true;

				//隐藏图标信息
				ClearSlot();

			}
		}
	}

	//先完成上述才做再调父类
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

}

bool UUI_InventorySlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	
	bool bDrop = false;

	//首先判断拖拽操作是否是有效的
	if (UDefenceDragDropOperation*DefenceDragDrop = Cast<UDefenceDragDropOperation>(InOperation))
	{
		//从当前拖拽事件中获取换成的途欢的UI
		if (UUI_InventorySlot* MyInvenrtorySlot = Cast<UUI_InventorySlot>(DefenceDragDrop->Payload))
		{
			//如果能获取成功，就开始进行当前slot位置的信息交换（交换由GameState执行）
			GetBuildingTower().bDragICO = false;  //关闭当前的拖拽状态

			//currentGUID 来自父类创建时自己生成的
			GetGameState()->RequestInvetorySlotSwap(CurrentGUID, MyInvenrtorySlot->CurrentGUID);
			
			//更新当前UI
			UpdateUI();
			MyInvenrtorySlot->UpdateUI();

			bDrop = true;  //释放完成

			//强制持续刷新UI
			ForceUpdateUITime = 0;

		}
	}

	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	return bDrop;
}

void UUI_InventorySlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	//当鼠标移动到UI上的时候
	if (!bLockGUID)
	{
		TowerICOGuid = CurrentGUID;
	}

}

void UUI_InventorySlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{

}

