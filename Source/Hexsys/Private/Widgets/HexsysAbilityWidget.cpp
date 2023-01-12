// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/HexsysAbilityWidget.h"
#include "Hexsys.h"
#include "Widgets/HexsysQualityWidget.h"

void UHexsysAbilityWidget::AddAbility(FHexsysAbility NewAbility)
{
	TArray<FName> Qualities;
	
	// When adding a new ability check if this widget has any linked qualities, if it does then build an array.
	for (const UHexsysQualityWidget* Element : LinkedQualities)
		if(Element != nullptr)
			Qualities.Add(Element->Quality.TraitName);
	
	// Update ability and widget data.
	NewAbility.Index = Index;
	Ability = NewAbility;
	
	// Add the ability to parent qualities
	HexsysCharacter->AddAbility(NewAbility, Index, Qualities);
}

void UHexsysAbilityWidget::UpdateAbility(FHexsysAbility NewAbility)
{
	// The ability we're trying to change.
	const FName OldAbility = HexsysCharacter->SheetMappedHexagons.Find(Index)->TraitName;
	TArray<FName> Qualities;

	// When updating an ability check if this widget has any linked qualities, if it does then build an array.
	// this process is required because we need to update this ability in any linked quality.
	for (const UHexsysQualityWidget* Element : this->LinkedQualities)
		if(Element != nullptr)
			Qualities.Add(Element->Quality.TraitName);
	
	// Update ability and widget data.
	NewAbility.Index = Index;
	Ability = NewAbility;
	
	// Change the character ability with a new one.
	HexsysCharacter->ChangeCharacterAbility(NewAbility,Qualities, OldAbility);
}

void UHexsysAbilityWidget::RemoveAbility(FName AbilityName)
{
	// Empty current ability.
	Ability = FHexsysAbility();
	
	TArray<FName> ParentQualities;
	for(const UHexsysQualityWidget* QualityWidget : LinkedQualities)
		ParentQualities.Add(QualityWidget->Quality.TraitName);
	
	// Remove ability.
	HexsysCharacter->RemoveAbility(AbilityName, ParentQualities);
	// These step is necessary to ensure ability removal even when
	// both parent qualities are invalid.
	HexsysCharacter->SheetMappedHexagons.Remove(Index);
}

void UHexsysAbilityWidget::OnInitialize(FHexsysHexagon* Hexagon)
{
	// If static_cast works that's the best solution.
	const FHexsysAbility* _Ability = static_cast<FHexsysAbility*>(Hexagon);
	if(_Ability != nullptr)
		Ability = *_Ability;
}

