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

	UFUNCTION(BlueprintCallable, meta=(DeterminesOutputType="Type"))
	FORCEINLINE UHexsysSystem* GetCharacterTrait(FName TraitName, TSubclassOf<UHexsysSystem> Type) const
	{
		UHexsysSystem* const* System = Systems.Find(TraitName);
		UE_LOG(LogTemp, Display, TEXT("%s"), System != nullptr? TEXT("True") : TEXT("False"))
		if(System != nullptr)
		     return *System;
		else
			return nullptr;
	}
	
private:
	
	UPROPERTY()
	TMap<FName, UHexsysSystem*> Systems;
	
};
