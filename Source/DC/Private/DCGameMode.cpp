// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "DC.h"
#include "DCGameMode.h"
#include "DCCharacter.h"
#include "DCPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "DCGameUIWidget.h"
#include "UI_Render.h"
#include "DCHUD.h"

ADCGameMode::ADCGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL) { DefaultPawnClass = PlayerPawnBPClass.Class; }
	HUDClass = ADCHUD::StaticClass();
}

void ADCGameMode::BeginPlay() {
	Super::BeginPlay();

	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It) {
		ADCPlayerController* PC = Cast<ADCPlayerController>(*It);
		if (PC) { PC->CreatePlayerWidgets(); }
	}
}
