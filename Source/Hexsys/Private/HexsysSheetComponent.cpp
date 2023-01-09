// Fill out your copyright notice in the Description page of Project Settings.

#include "HexsysSheetComponent.h"
#include "HexsysSystem.h"

// Sets default values for this component's properties
UHexsysSheetComponent::UHexsysSheetComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}

// Called when the game starts
void UHexsysSheetComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// Initialize archetype.
    const FHexsysArchetype Archetype = CharacterAsset->GetCharacterArchetype();
	if(Archetype.System != nullptr)
	{
		UHexsysArchetypeSystem* ArchetypeSystem = NewObject<UHexsysArchetypeSystem>(CharacterAsset, Archetype.System);
		ArchetypeSystem->ArchetypeData = Archetype;
		ArchetypeSystem->OnInitialize();
		Systems.Add(Archetype.TraitName, ArchetypeSystem);
	}
	
	// Initialize Qualities.
	for(const FHexsysQuality& Quality : CharacterAsset->GetCharacterQualities())
	{
		if(Quality.System != nullptr)
		{
			UHexsysQualitySystem* QualitySystem = NewObject<UHexsysQualitySystem>(CharacterAsset, Quality.System);
			QualitySystem->QualityData = Quality;
			QualitySystem->OnInitialize();
			Systems.Add(Quality.TraitName, QualitySystem);
		}
	}
	
	// Initialize Abilities.
	for(const FHexsysAbility& Ability : CharacterAsset->GetCharacterAbilities())
	{
		if(Ability.System != nullptr)
		{
			UHexsysAbilitySystem* AbilitySystem = NewObject<UHexsysAbilitySystem>(CharacterAsset, Ability.System);
			AbilitySystem->AbilityData = Ability;
			AbilitySystem->OnInitialize();
			Systems.Add(Ability.TraitName, AbilitySystem);
		}
	}
}

// Called every frame
void UHexsysSheetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
	// ...
}







