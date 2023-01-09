// Fill out your copyright notice in the Description page of Project Settings.

#include "HexsysCharacterFactory.h"
#include "HexsysCharacter.h"

UHexsysCharacterFactory::UHexsysCharacterFactory()
{
	SupportedClass = UHexsysCharacter::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* UHexsysCharacterFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags,
                                          UObject* Context, FFeedbackContext* Warn)
{
	// Create asset.
	return NewObject<UHexsysCharacter>(InParent, Class, Name, Flags, Context);
}






