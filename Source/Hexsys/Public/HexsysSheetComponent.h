// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HexsysCharacter.h"
#include "HexsysSystem.h"
#include "Components/ActorComponent.h"
#include "HexsysSheetComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HEXSYS_API UHexsysSheetComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	// Sets default values for this component's properties
	UHexsysSheetComponent();

	// If true component will work with a copy of HexSys character instead of directly
	// using the asset reference, meaning that all changes to the character should be saved manually.
	// N.B. When false every change to the character will propagate
	// to the original asset.
	UPROPERTY(EditAnywhere)
	bool UseAssetCopy = true;
	
	UPROPERTY(EditAnywhere, meta=(EditCondition="UseAssetCopy", EditConditionHides))
	TSoftObjectPtr<UHexsysCharacter> CharacterAsset;
	
	UPROPERTY(EditAnywhere, meta=(EditCondition="!UseAssetCopy", EditConditionHides))
	UHexsysCharacter* Character;

protected:
	
	// Called when the game starts
	virtual void BeginPlay() override;
    
public:
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Get the given character trait. if trait could not be found will return nullptr(Invalid object).
	UFUNCTION(BlueprintCallable)
	FORCEINLINE UHexsysSystem* GetCharacterTrait(FName TraitName) const
	{
		UHexsysSystem* const* System = Systems.Find(TraitName);
		if(System != nullptr)
		     return *System;
		else
			return nullptr;
	}

	// Add an archetype to this HexSys character. Returns true if archetype has been added, false otherwise.
	// N.B. If archetype already exists then this function will return false and fail, if you want to change an existing
	// archetype use 'ChangeArchetype' instead.
	UFUNCTION(BlueprintCallable, Category="HexSys Character sheet")
	bool AddArchetype(UHexsysArchetypeSystem* Archetype);

	// Change the archetype of this HexSys character with a new one. Returns true if archetype was changed, false otherwise
	UFUNCTION(BlueprintCallable, Category="HexSys Character sheet")
	bool ChangeArchetype(UHexsysArchetypeSystem* Archetype);

	// Remove the current archetype from this HexSys character.
	UFUNCTION(BlueprintCallable, Category="HexSys Character sheet")
	bool RemoveArchetype();
	
	// Add a quality to this HexSys character. Returns true if quality has been added, false otherwise.
	// N.B. If quality already exists then this function will return false and fail, if you want to change an existing
	// quality use 'ChangeQuality' instead.
	UFUNCTION(BlueprintCallable, Category="HexSys Character sheet")
	bool AddQuality(UHexsysQualitySystem* Quality, int SheetIndex);

	// Change a quality of this HexSys character with a new one. Returns true if quality was changed, false otherwise
	UFUNCTION(BlueprintCallable, Category="HexSys Character sheet")
	bool ChangeQuality(UHexsysQualitySystem* Quality, const FName OldQuality);

	// Remove the current quality from this HexSys character.
	UFUNCTION(BlueprintCallable, Category="HexSys Character sheet")
	bool RemoveQuality(FName Quality);
	
	// Add an ability to this HexSys character. Returns true if ability has been added, false otherwise.
	// N.B. If the ability already exists then this function will return false and fail, if you want to change an existing
	// ability use 'ChangeAbility' instead.
	UFUNCTION(BlueprintCallable, Category="HexSys Character sheet")
	bool AddAbility(UHexsysAbilitySystem* Ability, int SheetIndex, const TArray<FName> ParentQualities);

	// Change an ability of this HexSys character with a new one. Returns true if ability was changed, false otherwise
	UFUNCTION(BlueprintCallable, Category="HexSys Character sheet")
	bool ChangeAbility(UHexsysAbilitySystem* Ability, const TArray<FName> ParentQualities, const FName OldAbility);

	UFUNCTION(BlueprintCallable, Category="HexSys Character sheet")
	bool RemoveAbility(FName Ability, TArray<FName> ParentQualities);
	
private:

	// Map used to store Hexsys systems, can be queried to get the desired system.
	UPROPERTY()
	TMap<FName, UHexsysSystem*> Systems;

#if UE_EDITOR
    void LogWarning(EHexagonType Type);
#endif
};
