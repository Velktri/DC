// Fill out your copyright notice in the Description page of Project Settings.

#include "DC.h"
#include "DCPlayerController.h"
#include "DCGameUIWidget.h"
#include "UI_Render.h"
#include "DCMeleeWeapon.h"


ADCPlayerController::ADCPlayerController() {
	/* Generate an empty Inventory */
	MaxInventorySize = 30;
	Inventory.SetNum(MaxInventorySize, false);

	static ConstructorHelpers::FObjectFinder<UBlueprint> EquippableRenderBPClass(TEXT("Blueprint'/Game/Blueprints/UI_Render_BP.UI_Render_BP'"));
	if (EquippableRenderBPClass.Object) {
		EquippableRenderClass = (UClass*)EquippableRenderBPClass.Object->GeneratedClass;
	}

	bIsPaused = false;
}

void ADCPlayerController::BeginPlay() {
	Super::BeginPlay();

	FVector SpawnLoc = FVector(0.0f, 2000000.0f, 0.0f);
	FRotator Rot = FRotator(0.0f, 180.0f, 0.0f);
	if (EquippableRenderClass) {
		FActorSpawnParameters SpawnParams;
		EquippableRenderRef = GetWorld()->SpawnActor<AUI_Render>(EquippableRenderClass, SpawnLoc, Rot, SpawnParams);
	}
}

void ADCPlayerController::PrintInventory() {
	for (int32 i = Inventory.Num() - 1; i >= 0; i--) {
		ADCItem* Equippable = Inventory[i];
		if (Equippable) {
			FString string = "Slot " + FString::FromInt(i) + ": " + Equippable->GetItemName() + ".";
			UE_LOG(LogTemp, Warning, TEXT("%s"), *string);
		}
	}
}

void ADCPlayerController::PauseGame() {
	StartMenuWidget->AddToViewport();
	InGameUI->RemoveFromViewport();
	bIsPaused = SetPause(true);
}

void ADCPlayerController::ResumeGame() {
	bIsPaused = SetPause(false);
	FInputModeGameOnly inputType;
	SetInputMode(inputType);
	StartMenuWidget->RemoveFromViewport();
	InGameUI->AddToViewport();
}

void ADCPlayerController::SetupInputComponent() {
	Super::SetupInputComponent();

	/** Testing Inputs */
	InputComponent->BindAction("PrintInventory", IE_Pressed, this, &ADCPlayerController::PrintInventory);
	InputComponent->BindAction("StartMenu", IE_Pressed, this, &ADCPlayerController::PauseGame);
}

TArray<class ADCItem*> ADCPlayerController::GetInventory() {
	return Inventory;
}

void ADCPlayerController::AddToInventory(ADCItem* InItem) {
	int size = 0;
	for (size; size < MaxInventorySize; size++) {
		if (!Inventory[size]) {
			Inventory[size] = InItem;
			UE_LOG(LogTemp, Warning, TEXT("You picked up a %s."), *InItem->GetItemName());
			StartMenuWidget->AddInventoryItem(InItem);
			return;
		}
	}

	if (size == MaxInventorySize) {  UE_LOG(LogTemp, Warning, TEXT("Inventory is Full."));  }
}

UDCGameUIWidget* ADCPlayerController::GetInGameWidget() {
	return InGameUI;
}

class UDCGameUIWidget* ADCPlayerController::GetStartMenuWidget() {
	return StartMenuWidget;
}

void ADCPlayerController::EquipEquippable(ADCItem* InItem) {
	ADCMeleeWeapon* CurrentWeapon = CurrentEquipment.RightWeapon;
	if (CurrentWeapon == NULL) {
		CurrentWeapon = Cast<ADCMeleeWeapon>(InItem);
		CurrentWeapon->SetPlayerController(this);
		CurrentWeapon->OnEquip();
	} else {
		CurrentWeapon->OnUnEquip();
		CurrentWeapon = Cast<ADCMeleeWeapon>(InItem);
		CurrentWeapon->SetPlayerController(this);
		CurrentWeapon->OnEquip();
	}
}
