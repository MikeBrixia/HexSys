// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HexsysHexagon.h"
#include "HexsysCharacter.generated.h"

/**
 * Asset which stores all informations about an HexSys character.
 */
UCLASS(BlueprintType)
class HEXSYS_API UHexsysCharacter : public UObject
{
	GENERATED_BODY()

private:

	/* The character archetype. */
	UPROPERTY(EditDefaultsOnly)
	FHexsysArchetype Archetype;

	/* The character qualities. */
	UPROPERTY(EditDefaultsOnly)
	TMap<FName, FHexsysQuality> Qualities;

public:
    
	// Map the character to an HexSys sheet. This TMap can be used to build
	// the HexSys sheet UI.
	UPROPERTY(VisibleDefaultsOnly)
	TMap<int, FHexsysHexagon> SheetMappedHexagons;

	// Add a new archetype to this character.
	UFUNCTION(BlueprintCallable)
	void AddArchetype(FHexsysArchetype NewArchetype, int Index);

	// Remove the current character archetype
	UFUNCTION(BlueprintCallable)
	void RemoveArchetype();
	
	// Get the character archetype.
	// Archetypes are what defines an HexSys character, their core.
	UFUNCTION(BlueprintCallable)
	FORCEINLINE FHexsysArchetype GetCharacterArchetype() const { return Archetype; }
    
	// Change the character archetype.
	// Archetypes are what defines an HexSys character, their core. This function it's usefull
	// because the archetype can change overtime, when the character evolves/change.
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void ChangeCharacterArchetype(FHexsysArchetype NewArchetype)
	{
		SheetMappedHexagons.Add(0, NewArchetype);
		Archetype = NewArchetype;
	}
	
	//Get the given character quality.
	//Qualities describes the character personal traits.
	UFUNCTION(BlueprintCallable)
	FHexsysQuality GetCharacterQuality(FName QualityName) const;

	// Get all character abilities
	UFUNCTION(BlueprintCallable)
	TArray<FHexsysAbility> GetCharacterAbilities() const;
	
	// Change a character quality.
	// Qualities can change overtime, becoming stronger or a different trait.
	UFUNCTION(BlueprintCallable)
	void ChangeCharacterQuality(FHexsysQuality NewQuality, FName OldQuality);

	// Add a new quality to this hexsys character
	UFUNCTION(BlueprintCallable)
	void AddQuality(FHexsysQuality NewQuality, int Index);

	// Remove given quality from this character
	UFUNCTION(BlueprintCallable)
	void RemoveQuality(FName Quality);
	
	// Get the given character ability.
	// Abilities describes what a character can do or is capable of doing.
	UFUNCTION(BlueprintCallable)
	FHexsysAbility GetCharacterAbility(const FName Quality, const FName Ability) const;

	// Get the given character ability.
	// Abilities describes what a character can do or is capable of doing.
	// Abilities can change overtime, becoming stronger or a different trait.
	UFUNCTION(BlueprintCallable)
	void ChangeCharacterAbility(FHexsysAbility NewAbility, const TArray<FName> ParentQualities, const FName OldAbility);

	// Add a new ability to this character
	UFUNCTION(BlueprintCallable)
	void AddAbility(FHexsysAbility NewAbility, int Index, TArray<FName> ParentQualities);

	// Remove an ability from this character
	UFUNCTION(BlueprintCallable)
	void RemoveAbility(FName Ability, TArray<FName> ParentQualities);

	// Get all the character qualities.
	UFUNCTION(BlueprintCallable)
	TArray<FHexsysQuality> GetCharacterQualities() const;
	
};

