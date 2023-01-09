// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HexsysCharacter.h"
#include "HexsysHexagonWidget.generated.h"

/**
 * 
 */
UCLASS()
class HEXSYS_API UHexsysHexagonWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadOnly)
	UHexsysCharacter* HexsysCharacter = nullptr;
	
	UPROPERTY(EditAnywhere)
	int Index = 0;

	UPROPERTY(BlueprintReadOnly)
	FName Text;

	UFUNCTION(BlueprintImplementableEvent)
    void OnTextUpdated(FName UpdatedText);
	
	virtual void OnInitialize(FHexsysHexagon* Hexagon);
	
protected:

	// When trait name is "None" the trait will be considered invalid.
	const FName INVALID_TRAIT = "None";

	// When trait name is "" the trait will be considered invalid.
    const FName INVALID_TRAIT_1 = "";
	
	// Check if a trait is valid.
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsValidTrait(FName TraitName) const { return TraitName != INVALID_TRAIT && TraitName != INVALID_TRAIT_1; }
};


