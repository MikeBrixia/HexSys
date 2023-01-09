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
	
	UFUNCTION(BlueprintNativeEvent)
	void OnInitialize();
	virtual void OnInitialize_Implementation();

	UFUNCTION(BlueprintNativeEvent)
	void Execute();
	virtual void Execute_Implementation();
	
};

/**
 * 
 */
UCLASS(Blueprintable)
class HEXSYS_API UHexsysArchetypeSystem : public UHexsysSystem
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadOnly)
	FHexsysArchetype ArchetypeData;
};

/**
 *
 */
UCLASS(Blueprintable)
class HEXSYS_API UHexsysQualitySystem : public UHexsysSystem
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadOnly)
	FHexsysQuality QualityData;
};

/**
 * 
 */
UCLASS(Blueprintable)
class HEXSYS_API UHexsysAbilitySystem : public UHexsysSystem
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadOnly)
	FHexsysAbility AbilityData;
	
};

