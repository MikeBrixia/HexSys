// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/HexsysArchetypeWidget.h"

void UHexsysArchetypeWidget::AddArchetype(FHexsysArchetype NewArchetype)
{
	Archetype = NewArchetype;
	HexsysCharacter->AddArchetype(NewArchetype, Index);
}

void UHexsysArchetypeWidget::UpdateArchetype(FHexsysArchetype NewArchetype)
{
	Archetype = NewArchetype;
	HexsysCharacter->ChangeCharacterArchetype(NewArchetype);
}

void UHexsysArchetypeWidget::RemoveArchetype()
{
	Archetype = FHexsysArchetype();
	HexsysCharacter->RemoveArchetype();
}

void UHexsysArchetypeWidget::OnInitialize(FHexsysHexagon* Hexagon)
{
	const FHexsysArchetype* _Archetype = static_cast<FHexsysArchetype*>(Hexagon);
	if(_Archetype != nullptr)
		Archetype = *_Archetype;
}

