// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HexsysHexagon.generated.h"

class UHexsysArchetypeSystem;
class UHexsysQualitySystem;
class UHexsysAbilitySystem;

UENUM(BlueprintType)
enum class EHexagonType : uint8
{
	Archetype = 0 UMETA(DisplayName = "Archetype"),
	Quality = 1 UMETA(DisplayName = "Quality"),
	Ability = 2 UMETA(DisplayName = "Ability")
};

/* Base data structure for all HexSys hexagon data structure. */
USTRUCT(BlueprintType)
struct FHexsysHexagon
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	FName TraitName = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	EHexagonType HexagonType;
    
	UPROPERTY(VisibleDefaultsOnly)
	int Index = 0;
	
};

/* HexSys archetype data structure. */
USTRUCT(BlueprintType)
struct FHexsysArchetype : public FHexsysHexagon
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	TSubclassOf<UHexsysArchetypeSystem> System;
};

/* HexSys ability data structure. */
USTRUCT(BlueprintType)
struct FHexsysAbility : public FHexsysHexagon
{
	GENERATED_BODY()
    
public:

	UPROPERTY(EditAnywhere)
	TSubclassOf<UHexsysAbilitySystem> System;
};

/* HexSys quality data structure. */
USTRUCT(BlueprintType)
struct FHexsysQuality : public FHexsysHexagon
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	TSubclassOf<UHexsysQualitySystem> System;
	
	/* The abilities linked to this quality*/
	UPROPERTY(EditDefaultsOnly)
	TMap<FName, FHexsysAbility> Abilities;
	
};




