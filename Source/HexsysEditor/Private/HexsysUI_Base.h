// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "HexsysCharacter.h"
#include "HexsysUI_Base.generated.h"

/**
 * 
 */
UCLASS()
class UHexsysUI_Base : public UEditorUtilityWidget
{
	GENERATED_BODY()

public:
	
	// Initialize character 
	UFUNCTION(BlueprintCallable)
	void InitializeHexsysWidget(UHexsysCharacter* Character);
	
};
