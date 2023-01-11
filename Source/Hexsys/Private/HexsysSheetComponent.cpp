// Fill out your copyright notice in the Description page of Project Settings.

#include "HexsysSheetComponent.h"
#include "Hexsys.h"
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

bool UHexsysSheetComponent::AddArchetype(UHexsysArchetypeSystem* Archetype)
{
	bool Result = Archetype != nullptr && (CharacterAsset != nullptr && CharacterAsset->SheetMappedHexagons.Find(0) == nullptr);
	if(Result)
	{
		CharacterAsset->AddArchetype(Archetype->ArchetypeData, 0);
		Systems.Add(Archetype->ArchetypeData.TraitName, Archetype);
	}

#if UE_EDITOR
	else
		LogWarning(EHexagonType::Archetype);
#endif
	
	return Result;
}

bool UHexsysSheetComponent::ChangeArchetype(UHexsysArchetypeSystem* Archetype)
{
	bool Result = false;
	if(CharacterAsset != nullptr)
	{
		const FHexsysHexagon* OldArchetype = CharacterAsset->SheetMappedHexagons.Find(0);
		Result = Archetype != nullptr && OldArchetype != nullptr;
		if(Result)
		{
			Systems.Remove(OldArchetype->TraitName);
			Systems.Add(Archetype->ArchetypeData.TraitName, Archetype);
			CharacterAsset->ChangeCharacterArchetype(Archetype->ArchetypeData);
		}
	}
	return Result;
}

bool UHexsysSheetComponent::AddQuality(UHexsysQualitySystem* Quality, int SheetIndex)
{
	bool Result = Quality != nullptr && (CharacterAsset != nullptr && CharacterAsset->SheetMappedHexagons.Find(SheetIndex) == nullptr);
	if(Result)
	{
		CharacterAsset->AddQuality(Quality->QualityData, SheetIndex);
		Systems.Add(Quality->QualityData.TraitName, Quality);
	}
#if UE_EDITOR
	else
		LogWarning(EHexagonType::Quality);
#endif
	
	return Result;
}

bool UHexsysSheetComponent::ChangeQuality(UHexsysQualitySystem* Quality, const FName OldQuality)
{
	bool Result = Quality != nullptr && CharacterAsset != nullptr;
	if(Result)
	{
		CharacterAsset->ChangeCharacterQuality(Quality->QualityData, OldQuality);
		Systems.Remove(OldQuality);
		Systems.Add(Quality->QualityData.TraitName, Quality);
	}
	return Result;
}

bool UHexsysSheetComponent::AddAbility(UHexsysAbilitySystem* Ability, int SheetIndex, const TArray<FName> ParentQualities)
{
	bool Result = (Ability != nullptr &&  ParentQualities.Num() > 0) &&
		          (CharacterAsset != nullptr && CharacterAsset->SheetMappedHexagons.Find(SheetIndex) == nullptr);
	if(Result)
	{
		CharacterAsset->AddAbility(Ability->AbilityData, SheetIndex, ParentQualities);
		Systems.Add(Ability->AbilityData.TraitName, Ability);
	}
#if UE_EDITOR
	else
       LogWarning(EHexagonType::Ability);
#endif	
	return Result;
}

bool UHexsysSheetComponent::ChangeAbility(UHexsysAbilitySystem* Ability, const TArray<FName> ParentQualities,
	const FName OldAbility)
{
	bool Result = (Ability != nullptr && ParentQualities.Num() > 0) &&
		          (CharacterAsset != nullptr);
	if(Result)
	{
		Systems.Remove(OldAbility);
		Systems.Add(Ability->AbilityData.TraitName, Ability);
		CharacterAsset->ChangeCharacterAbility(Ability->AbilityData, ParentQualities, OldAbility);
	}
	return Result;
}

void UHexsysSheetComponent::LogWarning(EHexagonType Type)
{
	FString TypeName;
	switch(Type)
	{
	case EHexagonType::Archetype:
		TypeName = "Archetype ";
		break;

	case EHexagonType::Quality:
		TypeName = "Quality ";
		break;

	case EHexagonType::Ability:
		TypeName = "Ability ";
		break;
	}
	
	const FName WarningMessage = FName(CharacterAsset->GetName() + TypeName + "could already exist or be null");
	UE_LOG(HexsysLog, Warning, TEXT("Could not add archetype to: %s"), *WarningMessage.ToString());
}












