// Fill out your copyright notice in the Description page of Project Settings.

#include "HexsysUI_Base.h"
#include "Blueprint/WidgetTree.h"
#include "Widgets/HexsysHexagonWidget.h"

void UHexsysUI_Base::InitializeHexsysWidget(UHexsysCharacter* Character)
{
	TArray<UWidget*> HexagonButtons;
	
	// Initialize HexSys hexagons
	WidgetTree->GetAllWidgets(HexagonButtons);
	TArray<FHexsysHexagon> Hexagons;
	Character->SheetMappedHexagons.GenerateValueArray(Hexagons);
	
	// The iteration will start from 1 because at index 0 there is a canvas panel which we don't need
	// to initialize.
	for(int i = 1; i < HexagonButtons.Num(); i++)
	{
		UHexsysHexagonWidget* HexagonWidget = Cast<UHexsysHexagonWidget>(HexagonButtons[i]);
		if(HexagonWidget != nullptr)
		{
			HexagonWidget->HexsysCharacter = Character;
			FHexsysHexagon* Hexagon = Character->SheetMappedHexagons.Find(HexagonWidget->Index);
			if(Hexagon != nullptr)
			{
				HexagonWidget->OnInitialize(Hexagon);
				HexagonWidget->OnTextUpdated(Hexagon->TraitName);
			}
		}
	}
}


