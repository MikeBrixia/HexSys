// Fill out your copyright notice in the Description page of Project Settings.

#include "HexsysUI_Base.h"
#include "Blueprint/WidgetTree.h"
#include "Hexagons/HexsysTrait.h"
#include "Widgets/HexsysHexagonWidget.h"

void UHexsysUI_Base::InitializeHexsysWidget(UHexsysCharacter* Character)
{
	// Get all Hexagon widgets
	TArray<UWidget*> HexagonButtons;
	WidgetTree->GetAllWidgets(HexagonButtons);
	
	// The iteration will start from 1 because at index 0 there is a canvas panel which we don't need
	// to initialize.
	for(int i = 1; i < HexagonButtons.Num(); i++)
	{
		UHexsysHexagonWidget* HexagonWidget = Cast<UHexsysHexagonWidget>(HexagonButtons[i]);
		if(HexagonWidget != nullptr)
			HexagonWidget->HexsysCharacter = Character;
	}
}


