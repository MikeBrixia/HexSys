// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HexsysHexagon.h"
#include "HexsysSystem.generated.h"

/**
 * An Hexsys System is used to translate and execute
 * the trait description in an actual gameplay action.
 */
UCLASS(BlueprintType)
class HEXSYS_API UHexsysSystem : public UObject
{
	GENERATED_BODY()
	
public:

	// Called when this system gets created.
	UFUNCTION(BlueprintNativeEvent)
	void OnInitialize();
	virtual void OnInitialize_Implementation();

	// Called when this system is requested to execute it's functionality.
	UFUNCTION(BlueprintNativeEvent)
	void Execute();
	virtual void Execute_Implementation();
	
};

/**
 * A system which you can use to implement Archetype actions and functionalities.
 */
UCLASS(Blueprintable)
class HEXSYS_API UHexsysArchetypeSystem : public UHexsysSystem
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(BlueprintReadWrite)
	FHexsysArchetype ArchetypeData;
};

/**
 * A system which you can use to implement qualities actions and functionalities.
 */
UCLASS(Blueprintable)
class HEXSYS_API UHexsysQualitySystem : public UHexsysSystem
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(BlueprintReadWrite)
	FHexsysQuality QualityData;
};

/**
 * A system which you can use to implement abilities actions and functionalities.
 */
UCLASS(Blueprintable)
class HEXSYS_API UHexsysAbilitySystem : public UHexsysSystem
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(BlueprintReadWrite)
	FHexsysAbility AbilityData;
	
};

