// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HexsysTrait.h"
#include "HexsysHexagon.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FHexsysHexagon
{
	GENERATED_BODY()

	/* The name of this hexagon trait */
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	FName TraitName = "";
    
	// Brief description of what this hexagon can do.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Description;
	
	// This index represent the position of this Hexagon inside
	// the HexSys character sheet UI.
	UPROPERTY(VisibleDefaultsOnly)
	int Index = 0;

	/* The actual character trait */
	UPROPERTY(EditAnywhere, Instanced, BlueprintReadOnly)
	UHexsysTrait* Trait;
	
	/* Hexagons which are linked to this hexagon. */
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	TArray<FName> LinkedHexagons;
	
};

FORCEINLINE static bool operator==(const FHexsysHexagon& A, const FHexsysHexagon& B)
{
	return A.TraitName == B.TraitName;
}
