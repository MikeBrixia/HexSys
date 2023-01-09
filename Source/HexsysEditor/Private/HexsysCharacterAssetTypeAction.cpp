// Fill out your copyright notice in the Description page of Project Settings.
#include "HexsysCharacterAssetTypeAction.h"
#include "HexsysCharacter.h"
#include "HexsysCharacterAssetToolkit.h"

UClass* FHexsysCharacterAssetTypeAction::GetSupportedClass() const
{
	return UHexsysCharacter::StaticClass();
}

FText FHexsysCharacterAssetTypeAction::GetName() const
{
	return INVTEXT("Hexsys Character");
}

FColor FHexsysCharacterAssetTypeAction::GetTypeColor() const
{
	return FColor::White;
}

uint32 FHexsysCharacterAssetTypeAction::GetCategories()
{
	return EAssetTypeCategories::Misc;
}



void FHexsysCharacterAssetTypeAction::OpenAssetEditor(const TArray<UObject*>& InObjects,
                                                      TSharedPtr<class IToolkitHost> EditWithinLevelEditor)
{
	// Create Asset toolkit and initialize the asset editor.
	MakeShared<HexsysCharacterAssetToolkit>()->InitializeEditor(InObjects);
}
