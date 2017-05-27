// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "DC.h"
#include "DCGameMode.h"
#include "DCCharacter.h"
#include "DCPlayerController.h"

ADCGameMode::ADCGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	PlayerControllerClass = ADCPlayerController::StaticClass();
}
