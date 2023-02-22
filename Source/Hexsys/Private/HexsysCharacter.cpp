// Fill out your copyright notice in the Description page of Project Settings.

#include "HexsysCharacter.h"

UHexsysCharacter::UHexsysCharacter()
{
	// Initialize array size and fill it with nullptr elements.
	SheetMappedTraits.Init(FHexsysHexagon(), 19);
}

void UHexsysCharacter::UpdateTrait(FHexsysHexagon Hexagon, int SheetIndex)
{
	SheetMappedTraits[SheetIndex] = Hexagon;
	Traits.Add(Hexagon.TraitName, Hexagon);
}

void UHexsysCharacter::RemoveTrait(FName TraitName)
{
	const FHexsysHexagon Trait = GetCharacterTrait(TraitName);
	const int SheetIndex = SheetMappedTraits.Find(Trait);
	SheetMappedTraits[SheetIndex] = FHexsysHexagon();
	Traits.Remove(TraitName);
}


