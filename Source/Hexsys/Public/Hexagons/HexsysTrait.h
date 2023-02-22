// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "HexsysTrait.generated.h"

/**
 * Base class for Hexsys hexagons
 */
UCLASS(EditInlineNew, BlueprintType, Blueprintable)
class HEXSYS_API UHexsysTrait : public UObject
{
	GENERATED_BODY()

public:

	UHexsysTrait();
	
	UFUNCTION(BlueprintNativeEvent)
	void Init();
	virtual void Init_Implementation();
	
	/* Called when you want to execute this HexSys hexagon. */
	UFUNCTION(BlueprintNativeEvent)
	void Execute();
	virtual void Execute_Implementation();
	
};
