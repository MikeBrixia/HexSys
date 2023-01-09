// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HexsysHexagonWidget.h"
#include "HexsysQualityWidget.generated.h"

class UHexsysAbilityWidget;
/**
 * 
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

	UFUNCTION(BlueprintCallable)
	void AddQuality(FHexsysQuality NewQuality);

	UFUNCTION(BlueprintCallable)
	void UpdateQuality(FHexsysQuality NewQuality);

	UFUNCTION(BlueprintCallable)
	void RemoveQuality(FName QualityToRemove);
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE TArray<UHexsysAbilityWidget*> GetChildAbilities() const { return LinkedAbilities; }

	void OnInitialize(FHexsysHexagon* Hexagon) override;
};
