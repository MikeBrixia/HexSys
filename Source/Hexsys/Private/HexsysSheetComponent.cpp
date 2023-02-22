// Fill out your copyright notice in the Description page of Project Settings.

#include "HexsysSheetComponent.h"

// Sets default values for this component's properties
UHexsysSheetComponent::UHexsysSheetComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	// ...
}

// Called when the game starts
void UHexsysSheetComponent::BeginPlay()
{
	Super::BeginPlay();

	// Create asset copy from asset path.
	if(CharacterAsset != nullptr && UseAssetCopy)
	     Character = DuplicateObject<UHexsysCharacter>(CharacterAsset.Get(), this);
	
}

// Called every frame
void UHexsysSheetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
	// ...
}













