// Fill out your copyright notice in the Description page of Project Settings.

#include "HexsysCharacter.h"

void UHexsysCharacter::ChangeCharacterQuality(FHexsysQuality NewQuality, FName OldQuality)
{
	// Remove old quality from this character.
	Qualities.Remove(OldQuality);
	// Add the new quality .
	Qualities.Add(NewQuality.TraitName, NewQuality);
	// Map this quality to the HexSys sheet.
	SheetMappedHexagons.Add(NewQuality.Index, NewQuality);
}

void UHexsysCharacter::AddQuality(FHexsysQuality NewQuality, int Index)
{
	SheetMappedHexagons.Add(Index, NewQuality);
	Qualities.Add(NewQuality.TraitName, NewQuality);
}

void UHexsysCharacter::RemoveQuality(FName Quality)
{
	const FHexsysQuality* _Quality = Qualities.Find(Quality);
	if(_Quality != nullptr)
	{
		SheetMappedHexagons.Remove(_Quality->Index);
		Qualities.Remove(Quality);
	}
}

FHexsysAbility UHexsysCharacter::GetCharacterAbility(const FName Quality, const FName Ability) const
{
	const FHexsysQuality* _Quality = Qualities.Find(Quality);
	FHexsysAbility Result = FHexsysAbility();
	if(_Quality != nullptr)
	{
		const FHexsysAbility* _Ability = _Quality->Abilities.Find(Ability);
		if(_Ability != nullptr)
			Result = *_Ability;
	}
	return Result;
}

void UHexsysCharacter::ChangeCharacterAbility(FHexsysAbility NewAbility, const TArray<FName> ParentQualities,
	const FName OldAbility)
{
	if(ParentQualities.Num() > 0)
		SheetMappedHexagons.Add(NewAbility.Index, NewAbility);
	
	for(const FName& QualityName : ParentQualities)
	{
		FHexsysQuality* _Quality = Qualities.Find(QualityName);
		if(_Quality != nullptr)
		{
			_Quality->Abilities.Remove(OldAbility);
			_Quality->Abilities.Add(NewAbility.TraitName, NewAbility);
		}
	}
}

void UHexsysCharacter::AddAbility(FHexsysAbility NewAbility, int Index, TArray<FName> ParentQualities)
{
	for (const FName& Parent : ParentQualities)
	{
		FHexsysQuality* _Quality = Qualities.Find(Parent);
		if(_Quality != nullptr)
		{
			SheetMappedHexagons.Add(Index, NewAbility);
			_Quality->Abilities.Add(NewAbility.TraitName, NewAbility);
		}
	}
}

void UHexsysCharacter::RemoveAbility(FName Ability, TArray<FName> ParentQualities)
{
	for(const FName& QualityName : ParentQualities)
	{
		FHexsysQuality* Quality = Qualities.Find(QualityName);
		if(Quality != nullptr)
		{
			const FHexsysAbility* _Ability = Quality->Abilities.Find(Ability);
			if(_Ability != nullptr)
			{
				SheetMappedHexagons.Remove(_Ability->Index);
				Quality->Abilities.Remove(Ability);
			}
		}
	}
}

TArray<FHexsysQuality> UHexsysCharacter::GetCharacterQualities() const
{
	TArray<FHexsysQuality> QualityList;
	Qualities.GenerateValueArray(QualityList);
	return QualityList;
}

void UHexsysCharacter::AddArchetype(FHexsysArchetype NewArchetype, int Index)
{
	Archetype = NewArchetype;
	SheetMappedHexagons.Add(Index, NewArchetype);
}

void UHexsysCharacter::RemoveArchetype()
{
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
