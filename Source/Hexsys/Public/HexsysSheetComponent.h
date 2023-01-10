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

	UPROPERTY(EditAnywhere)
	UHexsysCharacter* CharacterAsset;
	
protected:
	
	// Called when the game starts
	virtual void BeginPlay() override;
    
public:
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UHexsysSystem* GetCharacterTrait(FName TraitName) const
	{
		UHexsysSystem* const* System = Systems.Find(TraitName);
		if(System != nullptr)
		     return *System;
		else
			return nullptr;
	}
	
private:
	
	UPROPERTY()
	TMap<FName, UHexsysSystem*> Systems;
	
};
