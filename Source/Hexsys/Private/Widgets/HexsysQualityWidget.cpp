// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/HexsysQualityWidget.h"
#include "HexsysCharacter.h"
#include "Widgets/HexsysAbilityWidget.h"

void UHexsysQualityWidget::AddQuality(FHexsysQuality NewQuality)
{
	// Initialize Quality with already existing abilities.
	for(const UHexsysAbilityWidget* AbilityWidget : LinkedAbilities)
	{
		const FHexsysAbility* Ability = &AbilityWidget->Ability;
		if(IsValidTrait(Ability->TraitName))
		    NewQuality.Abilities.Add(Ability->TraitName, *Ability);
	}
	
	// Store quality ref and Add it to asset
	NewQuality.Index = Index;
	Quality = NewQuality;
	HexsysCharacter->AddQuality(NewQuality, Index);
}

void UHexsysQualityWidget::UpdateQuality(FHexsysQuality NewQuality)
{
	// Initialize Quality with already existing abilities.
	for(const UHexsysAbilityWidget* AbilityWidget : LinkedAbilities)
	{
		const FHexsysAbility* Ability = &AbilityWidget->Ability;
		if(IsValidTrait(Ability->TraitName))
			NewQuality.Abilities.Add(Ability->TraitName, *Ability);
	}
	
	// Store updated quality ref and update the asset
	NewQuality.Index = Index;
	Quality = NewQuality;
	const FName OldQuality = HexsysCharacter->SheetMappedHexagons.Find(Index)->TraitName;
	HexsysCharacter->ChangeCharacterQuality(NewQuality, OldQuality);
}

void UHexsysQualityWidget::RemoveQuality(FName QualityToRemove)
{
	Quality = FHexsysQuality();
	HexsysCharacter->RemoveQuality(QualityToRemove);
}

void UHexsysQualityWidget::OnInitialize(FHexsysHexagon* Hexagon)
{
	Quality = HexsysCharacter->GetCharacterQuality(Hexagon->TraitName);;
}

