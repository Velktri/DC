// Fill out your copyright notice in the Description page of Project Settings.

#include "DC.h"
#include "DCInventoryMenu.h"
#include "DCInventorySlot.h"
#include "DCPlayerController.h"
#include "UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "UI_Render.h"

void UDCInventoryMenu::InitInventory() {
	if (OwningPC) {
		TArray<ADCItem*> Inventory = OwningPC->Inventory;
		for (int i = 0; i < Inventory.Num(); i++) {
			UDCInventorySlot* ChildWidget = CreateWidget<UDCInventorySlot>(OwningPC, InventorySlotClass);
			UUniformGridSlot* gridSlot = InventoryContents->AddChildToUniformGrid(ChildWidget);
			gridSlot->SetColumn(i % InventoryPanelWidth);
			gridSlot->SetRow(i / InventoryPanelWidth);
			gridSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
			gridSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
			if (Inventory[i]) { ChildWidget->UpdateAddedItem(Inventory[i]); }
		}
	}
}

void UDCInventoryMenu::TickFunc(float DeltaTime) {
	if (OwningPC && OwningPC->EquippableRenderRef) {
		FRotator rot = FRotator(0, 50 * DeltaTime, 0);
		Cast<AUI_Render>(OwningPC->EquippableRenderRef)->RenderMesh->AddLocalRotation(rot);
	}
}
