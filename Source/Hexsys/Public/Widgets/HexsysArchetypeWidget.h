// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HexsysHexagonWidget.h"
#include "HexsysArchetypeWidget.generated.h"

/**
 * Hexagon UI used to display and edit HexSys archetypes.
 */
UCLASS()
class HEXSYS_API UHexsysArchetypeWidget : public UHexsysHexagonWidget
{
	GENERATED_BODY()

public:
	
	// Reference to the character archetype.
	UPROPERTY(BlueprintReadOnly)
	FHexsysArchetype Archetype;

	// Add a new archetype to the inspected asset.
	UFUNCTION(BlueprintCallable)
	void AddArchetype(FHexsysArchetype NewArchetype);

	// Update the archetype on the inspected asset.
	UFUNCTION(BlueprintCallable)
	void UpdateArchetype(FHexsysArchetype NewArchetype);

	// Remove the archetype on the inspected asset.
	UFUNCTION(BlueprintCallable)
	void RemoveArchetype();

	// Initialize this widget
	void OnInitialize(FHexsysHexagon* Hexagon) override;
};
