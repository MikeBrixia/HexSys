// Fill out your copyright notice in the Description page of Project Settings.

#include "HexsysCharacterAssetToolkit.h"
#include "EditorUtilityWidgetBlueprint.h"
#include "HexsysCharacter.h"
#include "HexsysUI_Base.h"
#include "Blueprint/WidgetTree.h"

HexsysCharacterAssetToolkit::HexsysCharacterAssetToolkit()
{
	HexsysWidgetAsset = LoadObject<UEditorUtilityWidgetBlueprint>(nullptr, TEXT("/Hexsys/UI/HexsysUI.HexsysUI"));
	HexsysCharacterAsset = nullptr;
}

void HexsysCharacterAssetToolkit::InitializeEditor(const TArray<UObject*>& InObjects)
{
	HexsysCharacterAsset = Cast<UHexsysCharacter>(InObjects[0]);
	if(HexsysCharacterAsset != nullptr)
	{
		// Create new layout.
		const TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout("HexsysCharacterEditorLayout");

		// Create asset editor primary area.
		TSharedRef<FTabManager::FArea> PrimaryArea = FTabManager::NewPrimaryArea();

		// Create splitter and initialize it.
		TSharedRef<FTabManager::FSplitter> Splitter = FTabManager::NewSplitter();
		Splitter->SetSizeCoefficient(0.6f);
		Splitter->SetOrientation(Orient_Horizontal);

		// Create UI Stack and initialize it.
		TSharedRef<FTabManager::FStack> UIStack = FTabManager::NewStack();
		UIStack->SetSizeCoefficient(0.8f);
		UIStack->AddTab("HexsysCharacterUITab", ETabState::OpenedTab);

		// Create Details Stack and initialize it.
		TSharedRef<FTabManager::FStack> DetailsStack = FTabManager::NewStack();
		DetailsStack->SetSizeCoefficient(0.2f);
		DetailsStack->AddTab("HexsysCharacterDetailsTab", ETabState::OpenedTab);

		// Split tabs in the asset editor.
		Splitter->Split(UIStack);
		Splitter->Split(DetailsStack);

		// Split primary area from other splitted tabs.
		PrimaryArea->Split(Splitter);

		// Ad created area to the current layout
		Layout->AddArea(PrimaryArea);
		
        // Initialize Asset editor with the new layout.
		InitAssetEditor(EToolkitMode::Standalone, nullptr, "HexsysCharacterEditor",
		               Layout, true, true, InObjects);
	}
}

void HexsysCharacterAssetToolkit::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	// Initialize editor workspace.
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(INVTEXT("HexSys Character Editor"));

	// HexSys editor slate widget reference
	HexsysWidgetAsset->CreateUtilityWidget();
	
	UHexsysUI_Base* EditorUI = Cast<UHexsysUI_Base>(HexsysWidgetAsset->GetCreatedWidget());
	// Initialize HexSys hexagons
	EditorUI->InitializeHexsysWidget(HexsysCharacterAsset);
		
	// Register HexSys UI tab.
	FTabSpawnerEntry& SheetTab = InTabManager->RegisterTabSpawner("HexsysCharacterUITab",
		FOnSpawnTab::CreateLambda([=](const FSpawnTabArgs&)
	{
		return SNew(SDockTab)[EditorUI->TakeWidget()];
	}));
	SheetTab.SetDisplayName(INVTEXT("Character Sheet"));
	SheetTab.SetGroup(WorkspaceMenuCategory.ToSharedRef());
    
	// Create and initialize details tab.
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	FDetailsViewArgs DetailsViewArgs;
	DetailsViewArgs.NameAreaSettings = FDetailsViewArgs::HideNameArea;
	const TSharedRef<IDetailsView> DetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);

	// Set the object to be inspected by the details tab.
	DetailsView->SetObjects(TArray<UObject*>{ HexsysCharacterAsset });
	
	// Register details tab
	FTabSpawnerEntry& DetailsTab = InTabManager->RegisterTabSpawner("HexsysCharacterDetailsTab",
	FOnSpawnTab::CreateLambda([=](const FSpawnTabArgs&)
	{
		return SNew(SDockTab)[DetailsView];
	}));
	DetailsTab.SetDisplayName(INVTEXT("Details"));
	DetailsTab.SetGroup(WorkspaceMenuCategory.ToSharedRef());
	
}

void HexsysCharacterAssetToolkit::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	// Unregisters all tabs
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);
	InTabManager->UnregisterTabSpawner("HexsysCharacterUITab");
	InTabManager->UnregisterTabSpawner("HexsysCharacterDetailsTab");
}





