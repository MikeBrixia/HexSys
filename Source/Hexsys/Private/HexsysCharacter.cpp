// Fill out your copyright notice in the Description page of Project Settings.

#include "HexsysCharacter.h"

void UHexsysCharacter::ChangeCharacterQuality(FHexsysQuality NewQuality, FName OldQuality)
{
	// Remove the quality we want to change from this asset.
	Qualities.Remove(OldQuality);
	// Add the new quality to asset and map it to HexSys sheet.
	Qualities.Add(NewQuality.TraitName, NewQuality);
	SheetMappedHexagons.Add(NewQuality.Index, NewQuality);
}

void UHexsysCharacter::AddQuality(FHexsysQuality NewQuality, int Index)
{
	// Map quality to HexSys sheet and add it to this asset.
	SheetMappedHexagons.Add(Index, NewQuality);
	Qualities.Add(NewQuality.TraitName, NewQuality);
}

void UHexsysCharacter::RemoveQuality(FName Quality)
{
	// Find the quality we want to remove
	const FHexsysQuality* _Quality = Qualities.Find(Quality);
	if(_Quality != nullptr)
	{
		// Remove quality from asset.
		SheetMappedHexagons.Remove(_Quality->Index);
		Qualities.Remove(Quality);
	}
}

FHexsysAbility UHexsysCharacter::GetCharacterAbility(const FName Quality, const FName Ability) const
{
	// Parent Quality of the ability we are searching for.
	const FHexsysQuality* _Quality = Qualities.Find(Quality);
	// If no ability will be found, we're gonna return an empty ability(invalid ability).
	FHexsysAbility Result = FHexsysAbility();
	if(_Quality != nullptr)
	{
		// Ability we are searching for.
		const FHexsysAbility* _Ability = _Quality->Abilities.Find(Ability);
		// If we've found the ability set it as the result and return it.
		if(_Ability != nullptr)
			Result = *_Ability;
	}
	return Result;
}

void UHexsysCharacter::ChangeCharacterAbility(FHexsysAbility NewAbility, const TArray<FName> ParentQualities,
	const FName OldAbility)
{
	// If there is at least one parent quality then map the new ability
	// to the HexSys sheet.
	if(ParentQualities.Num() > 0)
		SheetMappedHexagons.Add(NewAbility.Index, NewAbility);

	// For each parent quality remove the old ability and replace it
	// with the new one.
	for(const FName& QualityName : ParentQualities)
	{
		FHexsysQuality* _Quality = Qualities.Find(QualityName);
		if(_Quality != nullptr) // Ensure that the quality we're searching for actually exists.
		{
			_Quality->Abilities.Remove(OldAbility);
			_Quality->Abilities.Add(NewAbility.TraitName, NewAbility);
		}
	}
}

void UHexsysCharacter::AddAbility(FHexsysAbility NewAbility, int Index, TArray<FName> ParentQualities)
{
	SheetMappedHexagons.Add(Index, NewAbility);
	// For each parent quality map the new ability to an HexSys sheet and add it
	// to the quality abilities.
	for (const FName& Parent : ParentQualities)
	{
		FHexsysQuality* _Quality = Qualities.Find(Parent);
		if(_Quality != nullptr) // Ensure that the quality we're searching for actually exists.
			_Quality->Abilities.Add(NewAbility.TraitName, NewAbility);
	}
}

void UHexsysCharacter::RemoveAbility(FName Ability, TArray<FName> ParentQualities)
{
	// Remove the given ability from each of the parent qualities.
	for(const FName& QualityName : ParentQualities)
	{
		FHexsysQuality* Quality = Qualities.Find(QualityName);
		if(Quality != nullptr) // Ensure that the quality we're searching for actually exists.
		{
			const FHexsysAbility* _Ability = Quality->Abilities.Find(Ability);
			if(_Ability != nullptr) // Ensure that the ability we're searching for actually exists.
			{
				// Remove ability from sheet map and parent qualities.
				SheetMappedHexagons.Remove(_Ability->Index);
				Quality->Abilities.Remove(Ability);
			}
		}
	}
}

TArray<FHexsysQuality> UHexsysCharacter::GetCharacterQualities() const
{
	// Get all quality map values and return them.
	TArray<FHexsysQuality> QualityList;
	Qualities.GenerateValueArray(QualityList);
	return QualityList;
}

void UHexsysCharacter::AddArchetype(FHexsysArchetype NewArchetype, int Index)
{
	// Set new archetype as the character archetype and map it to an HexSys sheet.
	Archetype = NewArchetype;
	SheetMappedHexagons.Add(Index, NewArchetype);
}

void UHexsysCharacter::RemoveArchetype()
{
	// Remove archetype from sheet map and empty the character archetype.
	SheetMappedHexagons.Remove(0);
	Archetype = FHexsysArchetype();
}

FHexsysQuality UHexsysCharacter::GetCharacterQuality(FName QualityName) const
{
	// Search for the requested quality
	const FHexsysQuality* Quality = Qualities.Find(QualityName);

	// if quality was found return it, otherwise return invalid quality.
	FHexsysQuality Result = Quality != nullptr? *Quality : FHexsysQuality();
	return Result;
}

TArray<FHexsysAbility> UHexsysCharacter::GetCharacterAbilities() const
{
	// All the character abilities.
	TArray<FHexsysAbility> Abilities;

	// All the character qualities
	TArray<FHexsysQuality> _Qualities;
	
	// Get all character qualities.
	this->Qualities.GenerateValueArray(_Qualities);

	// Build Abilities array.
	for(const FHexsysQuality Quality : _Qualities)
	{
		TArray<FHexsysAbility> QualityAbilities;
		Quality.Abilities.GenerateValueArray(QualityAbilities);
		Abilities.Append(QualityAbilities);
	}
	return Abilities;
}
