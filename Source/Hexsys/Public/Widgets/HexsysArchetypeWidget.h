// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HexsysHexagonWidget.h"
#include "HexsysArchetypeWidget.generated.h"

/**
 * 
 */
UCLASS()
class HEXSYS_API UHexsysArchetypeWidget : public UHexsysHexagonWidget
{
	GENERATED_BODY()

public:
	
	// Reference to the character archetype.
	UPROPERTY(BlueprintReadOnly)
	FHexsysArchetype Archetype;

	UFUNCTION(BlueprintCallable)
	void AddArchetype(FHexsysArchetype NewArchetype);

	UFUNCTION(BlueprintCallable)
	void UpdateArchetype(FHexsysArchetype NewArchetype);

	UFUNCTION(BlueprintCallable)
	void RemoveArchetype();

	void OnInitialize(FHexsysHexagon* Hexagon) override;
};
