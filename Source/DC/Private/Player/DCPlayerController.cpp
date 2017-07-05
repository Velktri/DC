// Fill out your copyright notice in the Description page of Project Settings.

#include "DC.h"
#include "DCPlayerController.h"
#include "DCGameUIWidget.h"
#include "UI_Render.h"
#include "DCArmor.h"
#include "DCShield.h"
#include "DCHUD.h"
#include "DCRangedWeapon.h"
#include "DCMeleeWeapon.h"


ADCPlayerController::ADCPlayerController() {
	/* Generate an empty Inventory */
	MaxInventorySize = 30;
	Inventory.SetNum(MaxInventorySize, false);
	bIsPaused = false;

	/* Generate Current Equipment */
	CurrentEquipment.Add(ESlotType::Head,			NULL);
	CurrentEquipment.Add(ESlotType::Shoulder,		NULL);
	CurrentEquipment.Add(ESlotType::Chest,			NULL);
	CurrentEquipment.Add(ESlotType::Legs,			NULL);
	CurrentEquipment.Add(ESlotType::Boots,			NULL);
	CurrentEquipment.Add(ESlotType::RightWeapon,	NULL);
	CurrentEquipment.Add(ESlotType::LeftWeapon,		NULL);
	CurrentEquipment.Add(ESlotType::RangedWeapon,	NULL);
}

void ADCPlayerController::BeginPlay() {
	Super::BeginPlay();

	FVector SpawnLoc = FVector(0.0f, 2000000.0f, 0.0f);
	FRotator Rot = FRotator(0.0f, 180.0f, 0.0f);
	if (EquippableRenderClass) {
		FActorSpawnParameters SpawnParams;
		EquippableRenderRef = GetWorld()->SpawnActor<AUI_Render>(EquippableRenderClass, SpawnLoc, Rot, SpawnParams);
		EquippableRenderRef->OwningPC = this;
	}
}

void ADCPlayerController::PauseGame() {
	StartMenuWidget->AddToViewport();
	Cast<ADCHUD>(GetHUD())->ToggleHUD();
	bIsPaused = SetPause(true);
}

void ADCPlayerController::ResumeGame() {
	bIsPaused = SetPause(false);
	FInputModeGameOnly inputType;
	SetInputMode(inputType);
	StartMenuWidget->RemoveFromViewport();
	Cast<ADCHUD>(GetHUD())->ToggleHUD();
}

void ADCPlayerController::SetupInputComponent() {
	Super::SetupInputComponent();

	/** Testing Inputs */
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

void ADCPlayerController::CreatePlayerWidgets() {
	if (StartMenuClass)
	{
		StartMenuWidget = CreateWidget<UDCGameUIWidget>(this, StartMenuClass);
		StartMenuWidget->OwningPC = this;
		FInputModeGameOnly inputType;
		SetInputMode(inputType);
	}

	if (EquippableRenderRef) { EquippableRenderRef->SetNewRenderMesh(GetPawn(), ECaptureStates::InGame); }
}

class UDCGameUIWidget* ADCPlayerController::GetStartMenuWidget() {
	return StartMenuWidget;
}

void ADCPlayerController::EquipEquippable(ADCEquippable* InItem) {
	if (InItem)
	{
		if (InItem->IsA(ADCArmor::StaticClass()))
		{
			EquipToSlot<ADCArmor>(InItem);
		} 
		else if (InItem->IsA(ADCMeleeWeapon::StaticClass()))
		{
			EquipToSlot<ADCMeleeWeapon>(InItem);
		} 
		else if (InItem->IsA(ADCRangedWeapon::StaticClass()))
		{
			EquipToSlot<ADCRangedWeapon>(InItem);
		}
		else if (InItem->IsA(ADCShield::StaticClass()))
		{
			EquipToSlot<ADCShield>(InItem);
		}
	}
}

template< class T >
void ADCPlayerController::EquipToSlot(ADCEquippable* InItem) {
	T* ArmorItem = Cast<T>(InItem);
	if (ArmorItem) {
		T* CurrentArmor = Cast<T>(CurrentEquipment[ArmorItem->SlotType]);
		if (CurrentArmor == NULL) {
			CurrentArmor = ArmorItem;
			CurrentArmor->SetPlayerController(this);
			CurrentArmor->OnEquip();
		} else {
			CurrentArmor->OnUnEquip();
			CurrentArmor = ArmorItem;
			CurrentArmor->SetPlayerController(this);
			CurrentArmor->OnEquip();
		}
		CurrentEquipment[ArmorItem->SlotType] = CurrentArmor;
	}
}
