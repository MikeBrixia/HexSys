// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HexsysHexagonWidget.h"
#include "HexsysQualityWidget.generated.h"

class UHexsysAbilityWidget;
/**
 * Hexagon UI used to display and edit HexSys qualities.
 */
UCLASS()
class HEXSYS_API UHexsysQualityWidget : public UHexsysHexagonWidget
{
	GENERATED_BODY()

public:

	// All the abilities widgets which are connected to this quality widget.
	UPROPERTY(EditAnywhere)
	TArray<UHexsysAbilityWidget*> LinkedAbilities;

	// Reference to the hexsys quality data contained inside this widget.
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FHexsysQuality Quality;

	// Add a quality to the currently inspected asset.
	UFUNCTION(BlueprintCallable)
	void AddQuality(FHexsysQuality NewQuality);

	// Update a quality on the currently inspected asset.
	UFUNCTION(BlueprintCallable)
	void UpdateQuality(FHexsysQuality NewQuality);

	// Remove a quality on the currently inspected asset
	UFUNCTION(BlueprintCallable)
	void RemoveQuality(FName QualityToRemove);
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE TArray<UHexsysAbilityWidget*> GetChildAbilities() const { return LinkedAbilities; }

	void OnInitialize(FHexsysHexagon* Hexagon) override;
};
