// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HexsysCharacter.h"
#include "Components/ActorComponent.h"
#include "HexsysSheetComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HEXSYS_API UHexsysSheetComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	// Sets default values for this component's properties
	UHexsysSheetComponent();

	// If true component will work with a copy of HexSys character instead of directly
	// using the asset reference, meaning that all changes to the character should be saved manually.
	// N.B. When false every change to the character will propagate
	// to the original asset.
	UPROPERTY(EditAnywhere)
	bool UseAssetCopy = true;
	
	UPROPERTY(EditAnywhere, meta=(EditCondition="UseAssetCopy", EditConditionHides))
	TSoftObjectPtr<UHexsysCharacter> CharacterAsset;

	/* The character contained inside this component. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition="!UseAssetCopy", EditConditionHides))
	UHexsysCharacter* Character;
	
protected:
	
	// Called when the game starts
	virtual void BeginPlay() override;
	
public:
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
};
