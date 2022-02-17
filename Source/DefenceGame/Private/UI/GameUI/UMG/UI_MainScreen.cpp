// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameUI/UMG/UI_MainScreen.h"
#include "DragDrop/DefenceDragDropOperation.h"
#include "UI/GameUI/UMG/Inventory/UI_InventorySlot.h"

void UUI_MainScreen::NativeConstruct()
{
	Super::NativeConstruct();


}

bool UUI_MainScreen::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{

	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	bool bDrop = false;

	if (UDefenceDragDropOperation* TargetDragDrop = Cast<UDefenceDragDropOperation>(InOperation))
	{
		if (UUI_InventorySlot* CurrentSlot = Cast<UUI_InventorySlot>(TargetDragDrop->Payload))
		{
			//拖拽状态设置为false，并更新UI
			CurrentSlot->GetBuildingTower().bDragICO = false;
			CurrentSlot->UpdateUI();

			bDrop = true;
		}
	}

	return bDrop;

}
