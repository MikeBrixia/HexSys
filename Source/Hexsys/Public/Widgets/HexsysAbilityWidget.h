// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HexsysHexagonWidget.h"
#include "HexsysAbilityWidget.generated.h"

class UHexsysQualityWidget;
/**
 * 
 */
UCLASS()
class HEXSYS_API UHexsysAbilityWidget : public UHexsysHexagonWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
	FHexsysAbility Ability;

	UPROPERTY(EditAnywhere)
	TArray<UHexsysQualityWidget*> LinkedQualities;

	UFUNCTION(BlueprintCallable)
	void AddAbility(FHexsysAbility NewAbility);

	UFUNCTION(BlueprintCallable)
	void UpdateAbility(FHexsysAbility NewAbility);

	UFUNCTION(BlueprintCallable)
	void RemoveAbility(FName AbilityName);
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE TArray<UHexsysQualityWidget*> GetParentQualities() const { return LinkedQualities; }

	void OnInitialize(FHexsysHexagon* Hexagon) override;
};
