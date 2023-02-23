// Fill out your copyright notice in the Description page of Project Settings.

#include "HexsysCharacter.h"

UHexsysCharacter::UHexsysCharacter()
{
	// Initialize array size and fill it with nullptr elements.
	SheetMappedTraits.Init(FHexsysHexagon(), 19);
}

void UHexsysCharacter::AddTrait(FHexsysHexagon Trait)
{
	// Is the new trait a valid trait? if yes go ahead and add it
	// to the character, otherwise ignore it.
	if(IsValidTrait(Trait.Name) && IsValidSheetIndex(Trait.SheetIndex))
	{
		SheetMappedTraits[Trait.SheetIndex] = Trait;
		Traits.Add(Trait.Name, Trait);

		// Notify listeners with the new added trait.
		if(OnTraitAdded.IsBound())
			OnTraitAdded.Broadcast(Trait);
	}
}

void UHexsysCharacter::AddChildTrait(FName ParentTrait, FHexsysHexagon ChildTrait)
{
	if(IsValidTrait(ParentTrait) && IsValidTrait(ChildTrait.Name))
	{
		// The parent trait of the new child trait.
		FHexsysHexagon Parent = GetCharacterTrait(ParentTrait);

		if(IsValidSheetIndex(Parent.SheetIndex) && IsValidSheetIndex(ChildTrait.SheetIndex))
		{
			// Add child trait to HexSys character.
			SheetMappedTraits[ChildTrait.SheetIndex] = ChildTrait;
			Traits.Add(ChildTrait.Name, ChildTrait);

			// Update parent trait
			Parent.ChildTraits.AddUnique(ChildTrait.Name);
			SheetMappedTraits[Parent.SheetIndex] = Parent;
			Traits.Add(Parent.Name, Parent);

			// Notify listeners with the new added child.
			if(OnTraitAdded.IsBound())
				OnTraitAdded.Broadcast(ChildTrait);
		}
	}
}

void UHexsysCharacter::UpdateTrait(FHexsysHexagon Trait)
{
	if(IsValidTrait(Trait.Name) && IsValidSheetIndex(Trait.SheetIndex))
	{
		// The character trait we want to update/change.
		const FHexsysHexagon OldTrait = SheetMappedTraits[Trait.SheetIndex];

		if(IsValidSheetIndex(OldTrait.SheetIndex))
		{
			// Update/change the old trait with the new one.
			Trait.ChildTraits = OldTrait.ChildTraits;
			SheetMappedTraits[Trait.SheetIndex] = Trait;
			Traits.Add(Trait.Name, Trait);
	
			// Once we've finished updating the character trait, notify all listeners.
			if(OnTraitUpdated.IsBound())
				OnTraitUpdated.Broadcast(Trait);
		}
	}
}

void UHexsysCharacter::UpdateChildTrait(TArray<FName> ParentTraits, FHexsysHexagon Trait)
{
	if(IsValidTrait(Trait.Name))
	{
		// The old trait we're trying to change.
		const FHexsysHexagon OldTrait = SheetMappedTraits[Trait.SheetIndex];
	
		for(const FName& ParentTrait : ParentTraits)
		{
			if(IsValidTrait(ParentTrait))
			{
				// The parent trait of this child.
				FHexsysHexagon Parent = GetCharacterTrait(ParentTrait);
	
				// Index of the trait we're trying to update. -1 if old trait could not be found
				const int OldChildIndex = Parent.ChildTraits.Find(OldTrait.Name);
				// If index of old trait was found, Update parent child with the new child trait name.
				if(IsValidSheetIndex(OldChildIndex))
				{
					Parent.ChildTraits[OldChildIndex] = Trait.Name;
					SheetMappedTraits[Parent.SheetIndex] = Parent;
					Traits.Add(Parent.Name, Parent);
				}
			}
		}

		// Update/change the old trait with the new one.
		Trait.ChildTraits = OldTrait.ChildTraits;
		SheetMappedTraits[Trait.SheetIndex] = Trait;
		Traits.Add(Trait.Name, Trait);

		// Notify listeners that trait has been updated with a new one.
		if(OnTraitUpdated.IsBound())
			OnTraitUpdated.Broadcast(Trait);
	}
}

void UHexsysCharacter::RemoveTrait(FName TraitName)
{
	const FHexsysHexagon Trait = GetCharacterTrait(TraitName);
	if (IsValidSheetIndex(Trait.SheetIndex) && IsValidTrait(Trait.Name))
	{
		SheetMappedTraits[Trait.SheetIndex] = FHexsysHexagon();
		Traits.Remove(TraitName);

		if (OnTraitRemoved.IsBound())
			OnTraitRemoved.Broadcast(Trait);
	}
}

void UHexsysCharacter::RemoveChildTrait(TArray<FName> ParentTraits, FName ChildTrait)
{
	if(IsValidTrait(ChildTrait))
	{
		// The child trait we're trying to remove.
		const FHexsysHexagon Child = GetCharacterTrait(ChildTrait);

		// Continue removing the trait only if it exists on the character.
		// If a character doesn't have a trait it's sheet index will be -1(invalid index
		// or INDEX_NONE)
		if(IsValidSheetIndex(Child.SheetIndex))
		{
			// Remove child trait from parent traits
			for(const FName& ParentTrait : ParentTraits)
			{
				if(IsValidTrait(ParentTrait) && IsValidTrait(ChildTrait))
				{
					FHexsysHexagon Parent = GetCharacterTrait(ParentTrait);
	
					// Update parent
					Parent.ChildTraits.Remove(ChildTrait);
					SheetMappedTraits[Parent.SheetIndex] = Parent;
					Traits.Add(Parent.Name, Parent);
				}
			}
			
			// Remove child.
			SheetMappedTraits[Child.SheetIndex] = FHexsysHexagon();
			Traits.Remove(ChildTrait);

			// Notify listeners about trait removal.
			if(OnTraitRemoved.IsBound())
				OnTraitRemoved.Broadcast(Child);
		}
	}
}


