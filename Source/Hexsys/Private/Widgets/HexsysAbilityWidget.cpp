// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/HexsysAbilityWidget.h"
#include "Widgets/HexsysQualityWidget.h"

void UHexsysAbilityWidget::AddAbility(FHexsysAbility NewAbility)
{
	TArray<FName> Qualities;
	for (const UHexsysQualityWidget* Element : LinkedQualities)
	{
		if(Element != nullptr)
			Qualities.Add(Element->Quality.TraitName);
	}
	NewAbility.Index = Index;
	Ability = NewAbility;
	HexsysCharacter->AddAbility(NewAbility, Index, Qualities);
}

void UHexsysAbilityWidget::UpdateAbility(FHexsysAbility NewAbility)
{
	const FName OldAbility = HexsysCharacter->SheetMappedHexagons.Find(Index)->TraitName;
	TArray<FName> Qualities;
	for (const UHexsysQualityWidget* Element : this->LinkedQualities)
	{
		if(Element != nullptr)
			Qualities.Add(Element->Quality.TraitName);
	}
	NewAbility.Index = Index;
	Ability = NewAbility;
	HexsysCharacter->ChangeCharacterAbility(NewAbility,Qualities, OldAbility);
}

void UHexsysAbilityWidget::RemoveAbility(FName AbilityName)
{
	Ability = FHexsysAbility();
	TArray<FName> ParentQualities;
	for(const UHexsysQualityWidget* QualityWidget : LinkedQualities)
		ParentQualities.Add(QualityWidget->Quality.TraitName);
	HexsysCharacter->RemoveAbility(AbilityName, ParentQualities);
}

void UHexsysAbilityWidget::OnInitialize(FHexsysHexagon* Hexagon)
{
	// If static_cast works that's the best solution.
	/*
	const FHexsysAbility* _Ability = static_cast<FHexsysAbility*>(Hexagon);
	if(_Ability != nullptr)
		Ability = *_Ability;
    */

	//Workaround solution to initialize Ability data in the widget in case
	// static_cast will not work
	FName Quality = "None";
	for(const UHexsysHexagonWidget* Widget : LinkedQualities)
	{
		Quality = HexsysCharacter->SheetMappedHexagons.Find(Widget->Index)->TraitName;
		if(IsValidTrait(Quality))
			break;
	}
	Ability = HexsysCharacter->GetCharacterAbility(Quality, Hexagon->TraitName);
}

