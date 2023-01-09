// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidgetBlueprint.h"
#include "HexsysCharacter.h"

/**
 * 
 */

class HexsysCharacterAssetToolkit : public FAssetEditorToolkit
{
	
public:

	HexsysCharacterAssetToolkit();
	
	/* Initialize HexSys character editor window and tabs. */
	void InitializeEditor(const TArray<UObject*>& InObjects);
	
	void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	
	void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	
	/* Update the asset UI with asset data */
    void UpdateAssetUI();

	//----------- IToolkit interface functions.
	
	FName GetToolkitFName() const override { return "HexsysCharacterToolkit"; }
	FText GetBaseToolkitName() const override { return INVTEXT("Hexsys Character Toolkit"); }
	FString GetWorldCentricTabPrefix() const override { return "Hexsys Character"; }
	FLinearColor GetWorldCentricTabColorScale() const override { return {}; }
	
	//-------------------|
	
private:

	UEditorUtilityWidgetBlueprint* HexsysWidgetAsset;
	UHexsysCharacter* HexsysCharacterAsset;
};
