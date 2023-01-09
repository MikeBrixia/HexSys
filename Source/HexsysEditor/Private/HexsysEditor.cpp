// Copyright Epic Games, Inc. All Rights Reserved.

#include "../Public/HexsysEditor.h"

#define LOCTEXT_NAMESPACE "FHexsysEditorModule"

void FHexsysEditorModule::StartupModule()
{
	if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		Asset = MakeShared<FHexsysCharacterAssetTypeAction>();
		FAssetToolsModule::GetModule().Get().RegisterAssetTypeActions(Asset.ToSharedRef());
		UE_LOG(LogTemp, Display, TEXT("Hexsys editor loaded"));
	}
}

void FHexsysEditorModule::ShutdownModule()
{
	if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	      FAssetToolsModule::GetModule().Get().UnregisterAssetTypeActions(Asset.ToSharedRef());
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FHexsysEditorModule, HexsysEditor)