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

	UPROPERTY(EditAnywhere)
	UHexsysCharacter* CharacterAsset;
	
protected:
	
	// Called when the game starts
	virtual void BeginPlay() override;
    
public:
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UHexsysSystem* GetCharacterTrait(FName TraitName) const
	{
		UHexsysSystem* const* System = Systems.Find(TraitName);
		if(System != nullptr)
		     return *System;
		else
			return nullptr;
	}

	UFUNCTION(BlueprintCallable)
	bool AddArchetype(UHexsysArchetypeSystem* Archetype);

	UFUNCTION(BlueprintCallable)
	bool ChangeArchetype(UHexsysArchetypeSystem* Archetype);

	UFUNCTION(BlueprintCallable)
	bool AddQuality(UHexsysQualitySystem* Quality, int SheetIndex);

	UFUNCTION(BlueprintCallable)
	bool ChangeQuality(UHexsysQualitySystem* Quality, const FName OldQuality);

	UFUNCTION(BlueprintCallable)
	bool AddAbility(UHexsysAbilitySystem* Ability, int SheetIndex, const TArray<FName> ParentQualities);

	UFUNCTION(BlueprintCallable)
	bool ChangeAbility(UHexsysAbilitySystem* Ability, const TArray<FName> ParentQualities, const FName OldAbility);
	
private:
	
	UPROPERTY()
	TMap<FName, UHexsysSystem*> Systems;

#if UE_EDITOR
    void LogWarning(EHexagonType Type);
#endif
};
