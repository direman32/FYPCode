// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "FYPGameMode.h"
#include "FYPHUD.h"
#include "FYPCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFYPGameMode::AFYPGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFYPHUD::StaticClass();
}
