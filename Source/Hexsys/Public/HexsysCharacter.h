// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hexagons/HexsysHexagon.h"
#include "HexsysCharacter.generated.h"

class UHexsysTrait;
/**
 * Asset which stores all informations about an HexSys character.
 */
UCLASS(BlueprintType)
class HEXSYS_API UHexsysCharacter : public UObject
{
	GENERATED_BODY()

private:

	/* Character traits, each trait on a HexSys character must be unique. */
	UPROPERTY()
	TMap<FName, FHexsysHexagon> Traits;
	
public:

	UHexsysCharacter();
	
	UPROPERTY(EditDefaultsOnly)
	TArray<FHexsysHexagon> SheetMappedTraits;

	/* Update one of this HexSys character traits. */
	UFUNCTION(BlueprintCallable, Category="HexSys")
	void UpdateTrait(FHexsysHexagon Hexagon, int SheetIndex);
	
	/* Remove a trait from this HexSys character. */
	UFUNCTION(BlueprintCallable, Category="HexSys")
	void RemoveTrait(FName TraitName);

	/* Get all the character traits. */
	UFUNCTION(BlueprintCallable, Category="HexSys")
	FORCEINLINE TArray<FHexsysHexagon> GetCharacterTraits() const
	{
		TArray<FHexsysHexagon> Hexagons;
		Traits.GenerateValueArray(Hexagons);
		return Hexagons;
	}

	/* Get one of the character traits. return nullptr(invalid object) if trait could not be found.*/
	UFUNCTION(BlueprintCallable, Category="HexSys")
	FORCEINLINE FHexsysHexagon GetCharacterTrait(FName TraitName) const
	{
		const FHexsysHexagon* Trait = Traits.Find(TraitName);
		return Trait != nullptr? *Trait : FHexsysHexagon();
	}
  
	/* Get the trait located at the current sheet index. */
	UFUNCTION(BlueprintCallable, Category="HexSys")
	FORCEINLINE FHexsysHexagon GetCharacterTraitAtSheetIndex(int SheetIndex) const
	{
		return SheetIndex < SheetMappedTraits.Num() && SheetIndex >= 0?
			                SheetMappedTraits[SheetIndex] : FHexsysHexagon();
	}
};

