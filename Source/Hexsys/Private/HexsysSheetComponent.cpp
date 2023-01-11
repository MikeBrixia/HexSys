// Fill out your copyright notice in the Description page of Project Settings.

#include "HexsysSheetComponent.h"
#include "Hexsys.h"
#include "HexsysSystem.h"

// Sets default values for this component's properties
UHexsysSheetComponent::UHexsysSheetComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	// ...
}

// Called when the game starts
void UHexsysSheetComponent::BeginPlay()
{
	Super::BeginPlay();

	// Create asset copy from asset path.
	if(CharacterAsset != nullptr && UseAssetCopy)
	     Character = DuplicateObject<UHexsysCharacter>(CharacterAsset.Get(), this);
	
	if(Character != nullptr)
	{
		// Initialize archetype.
		const FHexsysArchetype Archetype = Character->GetCharacterArchetype();
		if(Archetype.System != nullptr)
		{
			UHexsysArchetypeSystem* ArchetypeSystem = NewObject<UHexsysArchetypeSystem>(Character, Archetype.System);
			ArchetypeSystem->ArchetypeData = Archetype;
			ArchetypeSystem->OnInitialize();
			Systems.Add(Archetype.TraitName, ArchetypeSystem);
		}
	
		// Initialize Qualities.
		for(const FHexsysQuality& Quality : Character->GetCharacterQualities())
		{
			if(Quality.System != nullptr)
			{
				UHexsysQualitySystem* QualitySystem = NewObject<UHexsysQualitySystem>(Character, Quality.System);
				QualitySystem->QualityData = Quality;
				QualitySystem->OnInitialize();
				Systems.Add(Quality.TraitName, QualitySystem);
			}
		}
	
		// Initialize Abilities.
		for(const FHexsysAbility& Ability : Character->GetCharacterAbilities())
		{
			if(Ability.System != nullptr)
			{
				UHexsysAbilitySystem* AbilitySystem = NewObject<UHexsysAbilitySystem>(Character, Ability.System);
				AbilitySystem->AbilityData = Ability;
				AbilitySystem->OnInitialize();
				Systems.Add(Ability.TraitName, AbilitySystem);
			}
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
	bool Result = Archetype != nullptr && (Character != nullptr && Character->SheetMappedHexagons.Find(0) == nullptr);
	if(Result)
	{
		Character->AddArchetype(Archetype->ArchetypeData, 0);
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
	if(Character != nullptr)
	{
		const FHexsysHexagon* OldArchetype = Character->SheetMappedHexagons.Find(0);
		Result = Archetype != nullptr && OldArchetype != nullptr;
		if(Result)
		{
			Systems.Remove(OldArchetype->TraitName);
			Systems.Add(Archetype->ArchetypeData.TraitName, Archetype);
			Character->ChangeCharacterArchetype(Archetype->ArchetypeData);
		}
	}
	return Result;
}

bool UHexsysSheetComponent::RemoveArchetype()
{
	bool CanRemove = Character != nullptr;
	if(CanRemove)
	{
		const FName ArchetypeName = Character->SheetMappedHexagons.Find(0)->TraitName;
		Systems.Remove(ArchetypeName);
		Character->RemoveArchetype();
	}
	return CanRemove;
}

bool UHexsysSheetComponent::AddQuality(UHexsysQualitySystem* Quality, int SheetIndex)
{
	bool Result = Quality != nullptr && (Character != nullptr && Character->SheetMappedHexagons.Find(SheetIndex) == nullptr);
	if(Result)
	{
		Character->AddQuality(Quality->QualityData, SheetIndex);
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
	bool Result = Quality != nullptr && Character != nullptr;
	if(Result)
	{
		Character->ChangeCharacterQuality(Quality->QualityData, OldQuality);
		Systems.Remove(OldQuality);
		Systems.Add(Quality->QualityData.TraitName, Quality);
	}
	return Result;
}

bool UHexsysSheetComponent::RemoveQuality(FName Quality)
{
	bool CanRemove = Character != nullptr;
	if(Character != nullptr)
	{
		Systems.Remove(Quality);
		Character->RemoveQuality(Quality);
	}
	return CanRemove;
}

bool UHexsysSheetComponent::AddAbility(UHexsysAbilitySystem* Ability, int SheetIndex, const TArray<FName> ParentQualities)
{
	bool Result = (Ability != nullptr &&  ParentQualities.Num() > 0) &&
		          (Character != nullptr && Character->SheetMappedHexagons.Find(SheetIndex) == nullptr);
	if(Result)
	{
		Character->AddAbility(Ability->AbilityData, SheetIndex, ParentQualities);
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
		          (Character != nullptr);
	if(Result)
	{
		Systems.Remove(OldAbility);
		Systems.Add(Ability->AbilityData.TraitName, Ability);
		Character->ChangeCharacterAbility(Ability->AbilityData, ParentQualities, OldAbility);
	}
	return Result;
}

bool UHexsysSheetComponent::RemoveAbility(FName Ability, TArray<FName> ParentQualities)
{
	bool CanRemove = Character != nullptr;
	if(CanRemove)
	{
		Systems.Remove(Ability);
		Character->RemoveAbility(Ability, ParentQualities);
	}
	return CanRemove;
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
	
	const FName WarningMessage = FName(Character->GetName() + TypeName + "could already exist or be null");
	UE_LOG(HexsysLog, Warning, TEXT("Could not add archetype to: %s"), *WarningMessage.ToString());
}












