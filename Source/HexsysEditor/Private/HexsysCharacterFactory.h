// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HexsysCharacter.h"
#include "Factories/Factory.h"
#include "HexsysCharacterFactory.generated.h"

/**
 * 
 */
UCLASS()
class UHexsysCharacterFactory : public UFactory
{
	GENERATED_BODY()

public:

	UHexsysCharacterFactory();
	UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	
};
