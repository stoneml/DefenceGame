// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameUI/UMG/Tip/UI_TowerTip.h"
#include "Data/Core/CharacterData.h"
#include "Components/TextBlock.h"
#include "Components/MultiLineEditableText.h"

void UUI_TowerTip::InitTip(const FCharacterData& InData)
{
	CharacterNameBlock->SetText(FText::FromName(InData.Name));
	ConsumeGoldBlock->SetText(FText::AsNumber(InData.Gold));
	CharacterHealthBlock->SetText(FText::AsNumber(InData.MaxHealth));
	CharacterAttackBlock->SetText(FText::AsNumber(InData.PhysicalAttack));
	CharacterAttackSpeedBlock->SetText(FText::AsNumber(InData.AttackSpeed));
	CharacterArmorBlock->SetText(FText::AsNumber(InData.Armor));
	IntroductionBox->SetText(InData.Introduction);

}
