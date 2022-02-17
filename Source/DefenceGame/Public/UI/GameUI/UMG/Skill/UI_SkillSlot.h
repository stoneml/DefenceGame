// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Core/UI_Slot.h"
#include "UI_SkillSlot.generated.h"

/**
 * 
 */

class UImage;
class UTextBlock;
class UButton;

UCLASS()
class DEFENCEGAME_API UUI_SkillSlot : public UUI_Slot
{
	GENERATED_BODY()
	

private:

	//����ͼ��
	UPROPERTY(meta = (BindWidget))
		UImage* SkillIcon;

	//����CD�ɰ�ͼƬ
	UPROPERTY(meta = (BindWidget))
		UImage* SkillIconCD;

	//��������
	UPROPERTY(meta = (BindWidget))
		UTextBlock* SkillNumber;

	//��������
	UPROPERTY(meta = (BindWidget))
		UTextBlock* KeyValueNumber;

	//����CD�����ַ�ʽ��ʾ
	UPROPERTY(meta = (BindWidget))
		UTextBlock* SkilCDValue;

	//����������������԰����̻����Ե�����ʹ�ã�
	UPROPERTY(meta = (BindWidget))
		UButton* ClickButton;

public:

	virtual void NativeConstruct();

	//�������Ӧ����
	UFUNCTION()
		void OnReleasedWidget();

};