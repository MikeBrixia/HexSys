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
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	FName Name = "";
    
	// Brief description of what this hexagon can do.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;
	
	// This index represent the position of this Hexagon inside
	// the HexSys character sheet UI. this index is used when you need
	// to map the HexSys data to a sheet or UI asset.
	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly)
	int SheetIndex = INDEX_NONE;

	/* The actual character trait */
	UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite)
	UHexsysTrait* Trait;
	
	/* Hexagons which are linked to this hexagon. */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	TArray<FName> ChildTraits;

	FORCEINLINE bool operator==(const FHexsysHexagon& B) const
	{
		return Name == B.Name;
	}
};


