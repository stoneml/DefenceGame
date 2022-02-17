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

	//�󶨰�ť
	TISButton->OnReleased.AddDynamic(this, &UUI_InventorySlot::OnReleasedWidget);

	//���CDͼƬ����
	if (TowerCD)
	{
		CDMaterialDynamic = TowerCD->GetDynamicMaterial();
	}

	
}

void UUI_InventorySlot::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	//���û������ͣ״̬���ͽ���ˢ��
	if (GetBuildingTower().IsValid())
	{
		if (!GetBuildingTower().bLockCD)
		{
			//�Ƿ�����ק
			if (!GetBuildingTower().bDragICO)
			{
				//���µ�ǰCD
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

// 	�� ���ʱ��Ҫ�жϵ�ǰBuildingTowers�Ƿ������塣
// 	�� Ȼ���жϵ�ǰ����������㹺��tower��needgold����������ʱ����Ϊ1��
// 	�� Ȼ�������׼����������++��TowersPerpareBuildingNumber��
// 	�� ���жϵ�ǰ�Ľ���CD�� <= 0
// 	�� ����Ǿ�Ҫreset��ǰCD

	if (GetBuildingTower().IsValid())
	{
		if (/*GetBuildingTower().NeedGold*/ 1)
		{
			//��ʼ���н����Ŷ�
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

	//�ж�ͼƬ�Ƿ���Ч
	if (GetBuildingTower().Icon)
	{
		//�����Ч�ͽ���ͼƬ�����
		TowerIcon->SetBrushFromSoftTexture(GetBuildingTower().Icon);
		TowerIcon->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else
	{
		TowerIcon->SetVisibility(ESlateVisibility::Hidden);
	}

	//�Ե�ǰ�ƶ����UI������ʾ�ж�
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
	//�Ӹ����ȡ����ǰ��GameState
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

		//�ж�һ�������Ƿ�����Ч��
		if (TempData.IsValid())
		{
			//�����Ч��ô�Ϳ�ʼ���ɶ�ӦUI
			if (UUI_TowerTip* TipUI = CreateWidget<UUI_TowerTip>(GetWorld(), TipUIClass))
			{
				TipUI->InitTip(TempData);
				return TipUI;
			}
		}
	}

	//û�л�ȡ���ͷ��ؿ�
	return nullptr;
}

void UUI_InventorySlot::UpdateTowersCD(float InDataTime)
{
	//�����ǰ�������CD����0��Ҳ�����������ڽ���
	if (GetBuildingTower().CurrentConstrictionTowersCD>0)
	{
		//����CD����
		DrawTowersCD(GetBuildingTower().GetTowerConstructionTimePercentage());
		//CD�ݼ�
		GetBuildingTower().CurrentConstrictionTowersCD -= InDataTime;
		//�������ݸ���
		GetBuildingTower().bCallUpdateTowerInfo = true;
		//������Ϣ
		UpdateTowersBuildingInfo();
	}
	else if (GetBuildingTower().bCallUpdateTowerInfo)
	{
		GetBuildingTower().bCallUpdateTowerInfo = false;
		//׼����������
		//�������
		GetBuildingTower().TowersPerpareBuildingNumber--;

		//�����õ�+1
		GetBuildingTower().TowersConstructionNumber++; 

		//��CD�������
		DrawTowersCD(0.0f);

		//���׼��������������������0����ô������CD

		if (GetBuildingTower().TowersPerpareBuildingNumber>0)
		{
			GetBuildingTower().ResetCD();
		}
		//��������Ϣ
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
			//��ʼ����ʱ��ʱ����ʾ
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
		//%02d ��Ϊ���������� 00 �� 01 ��02����ʽ��ʾ
		TextNumberBlock->SetText(FText::FromString(FString::Printf(TEXT("%02d"), TextNumber)));
		TextNumberBlock->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
}

void UUI_InventorySlot::UpdateTowersBuildingInfo()
{
// 		�� ��ʾ��CD
// 		�� ������ɵ�����
// 		�� ����׼����������������

	DisplayNumber(TowerCDValue, GetBuildingTower().CurrentConstrictionTowersCD);
	DisplayNumber(TCOCNumber, GetBuildingTower().TowersConstructionNumber);
	DisplayNumber(TPBNumber, GetBuildingTower().TowersPerpareBuildingNumber);
}

FReply UUI_InventorySlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	//�ж��Ƿ�������Ҽ���������Ǵ����¼���������
	if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton || InMouseEvent.IsTouchEvent())
	{
		//����һ��������Ӧ
		FReply Reply = FReply::Handled();
		//����һ������ָ�룬����SWidget��һ������
		TSharedPtr<SWidget>SlateWidgetDrag = GetCachedWidget();

		if (SlateWidgetDrag.IsValid())
		{
			//������㻺����Ч����ô����ʾ��⵽��ק�¼���֮��ἤ��NativeOnDragDetected
			//������Ҫ������ָ��תΪ�������á�
			Reply.DetectDrag(SlateWidgetDrag.ToSharedRef(), EKeys::RightMouseButton);
			return Reply;
		}
	}
	return FReply::Handled();
}

void UUI_InventorySlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	//���Ȼ�ȡ��ǰSlot������Ϣ
	if (GetBuildingTower().IsValid() && IconDragUIClass)
	{
		//����һ��DragUI
		if (UUI_ICODragDrop* DragUIWidget = CreateWidget<UUI_ICODragDrop>(GetWorld(), IconDragUIClass))
		{
			//����һ����ק�¼�
			if (UDefenceDragDropOperation* DefenceDragOp = NewObject<UDefenceDragDropOperation>(GetTransientPackage(), UDefenceDragDropOperation::StaticClass()))
			{
				//GetTransientPackage() 
				//���Ϊǿ���ã��������ױ�����
				DefenceDragOp->SetFlags(RF_StrongRefOnFrame);
				//����ͼ��
				DragUIWidget->SetDrawICON(GetBuildingTower().Icon);  //��ֵ��UI��Icon�ǿյ�
				//���Լ���ֵ��һ�����ͼ�꣬����ק����ʾһ��һģһ�����Լ�
				//DefenceDragOp->DefaultDragVisual = DefenceDragOp;  ��δ���������
				DefenceDragOp->DefaultDragVisual = this;
				//�������ƶ�������һ�����ӵ�ʱ�����PayLoad��
				DefenceDragOp->Payload = this;
				//������ק��Ӧ�¼�
				OutOperation = DefenceDragOp;

				GetBuildingTower().bDragICO = true;

				//����ͼ����Ϣ
				ClearSlot();

			}
		}
	}

	//��������������ٵ�����
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

}

bool UUI_InventorySlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	
	bool bDrop = false;

	//�����ж���ק�����Ƿ�����Ч��
	if (UDefenceDragDropOperation*DefenceDragDrop = Cast<UDefenceDragDropOperation>(InOperation))
	{
		//�ӵ�ǰ��ק�¼��л�ȡ���ɵ�;����UI
		if (UUI_InventorySlot* MyInvenrtorySlot = Cast<UUI_InventorySlot>(DefenceDragDrop->Payload))
		{
			//����ܻ�ȡ�ɹ����Ϳ�ʼ���е�ǰslotλ�õ���Ϣ������������GameStateִ�У�
			GetBuildingTower().bDragICO = false;  //�رյ�ǰ����ק״̬

			//currentGUID ���Ը��ഴ��ʱ�Լ����ɵ�
			GetGameState()->RequestInvetorySlotSwap(CurrentGUID, MyInvenrtorySlot->CurrentGUID);
			
			//���µ�ǰUI
			UpdateUI();
			MyInvenrtorySlot->UpdateUI();

			bDrop = true;  //�ͷ����

			//ǿ�Ƴ���ˢ��UI
			ForceUpdateUITime = 0;

		}
	}

	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	return bDrop;
}

void UUI_InventorySlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	//������ƶ���UI�ϵ�ʱ��
	if (!bLockGUID)
	{
		TowerICOGuid = CurrentGUID;
	}

}

void UUI_InventorySlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{

}

