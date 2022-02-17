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

	//��ͼ��
	UPROPERTY(meta = (BindWidget))
		UImage* TowerIcon;

	//��CD�ɰ�ͼƬ
	UPROPERTY(meta = (BindWidget))
		UImage* TowerCD;

	//����������
	//Tower Prepare Building Number
	UPROPERTY(meta = (BindWidget))
		UTextBlock* TPBNumber;

	//�������������
	//Tower Completion Of Construction Number
	UPROPERTY(meta = (BindWidget))
		UTextBlock* TCOCNumber;

	//������CD
	UPROPERTY(meta = (BindWidget))
		UTextBlock* TowerCDValue;

	//����������������԰����̻����Ե�����ʹ�ã�
	//Tower Inverntory Slot Button
	UPROPERTY(meta = (BindWidget))
		UButton* TISButton;


	//������CD����ز���,���������ֽ����ǲ��ʵĽڵ��������
	UPROPERTY(EditDefaultsOnly,Category = UI)
	FName TowersMatCDName;

	UPROPERTY(EditDefaultsOnly,Category = UI)
	FName TowersClearValueName;


/*
	//��ʱ�ò�������ק
	UPROPERTY(EditDefaultsOnly,Category = UI)
	TSubclassOf<class UDefenceDragDropOperation> IcoDragDrop;*/

	//����UITip
	UPROPERTY(EditDefaultsOnly,Category = Tip)
	TSubclassOf<class UUI_TowerTip> TipUIClass;

	//����һ����קUI
	UPROPERTY(EditDefaultsOnly,Category = UI)
	TSubclassOf<class UUI_ICODragDrop> IconDragUIClass;

	//CD�Ķ�̬����
	UPROPERTY()
	class UMaterialInstanceDynamic* CDMaterialDynamic;




	//���Դ��루��ק������أ�
	int32 ForceUpdateUITime = 50;


public:

	virtual void NativeConstruct();

	//ʹ��Tick���������ݵ�ˢ��
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	//����¼�����
	UFUNCTION()
		void OnReleasedWidget();

	//���µ�ǰUI��Ϣ
	void UpdateUI();

	//��ȡ��ǰ����Ϣ
	FBuildingTower& GetBuildingTower();

	//����һ����������Slot��Ϣ�ĺ���
	void ClearSlot();


	//��TipUI��¶����ͼ
	UFUNCTION(BlueprintCallable,BlueprintPure,Category = Tip)
	UWidget* GetTowerTip();

private:
	//�����ڲ�ִ�нӿ�

	void UpdateTowersCD(float InDataTime);
	void DrawTowersCD(float InTowerCD);
	void DisplayNumber(UTextBlock* TextNumberBlock, int32 TextNumber);
	void UpdateTowersBuildingInfo();


protected:

	//�����ק�¼���غ���
	//�����
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	//�����ק���
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation);
	//�����ק�ͷ�
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);
	//������
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	//����뿪
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent);


};
