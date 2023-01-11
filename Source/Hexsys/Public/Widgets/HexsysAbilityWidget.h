// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HexsysHexagonWidget.h"
#include "HexsysAbilityWidget.generated.h"

class UHexsysQualityWidget;
/**
 * Hexagon UI used to display and edit an HexSys ability.
 */
UCLASS()
class HEXSYS_API UHexsysAbilityWidget : public UHexsysHexagonWidget
{
	GENERATED_BODY()

public:

	// Ability data contained inside this hexagon.
	UPROPERTY(BlueprintReadWrite)
	FHexsysAbility Ability;

	// Parent qualities.
	UPROPERTY(EditAnywhere)
	TArray<UHexsysQualityWidget*> LinkedQualities;

	// Add an ability to the currently inspected asset.
	UFUNCTION(BlueprintCallable)
	void AddAbility(FHexsysAbility NewAbility);

	// Update an ability on the currently inspected asset.
	UFUNCTION(BlueprintCallable)
	void UpdateAbility(FHexsysAbility NewAbility);

	// Remove an ability on the currently inspected asset.
	UFUNCTION(BlueprintCallable)
	void RemoveAbility(FName AbilityName);

	// Get all parent qualities.
	UFUNCTION(BlueprintCallable)
	FORCEINLINE TArray<UHexsysQualityWidget*> GetParentQualities() const { return LinkedQualities; }
    
	void OnInitialize(FHexsysHexagon* Hexagon) override;
};
