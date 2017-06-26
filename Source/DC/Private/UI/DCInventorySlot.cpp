// Fill out your copyright notice in the Description page of Project Settings.

#include "DC.h"
#include "DCInventorySlot.h"
#include "DCTypes.h"
#include "DCPlayerController.h"
#include "UI_Render.h"
#include "DCItem.h"
#include "Button.h"

void UDCInventorySlot::ItemClick() {
	if (OwningPC && OwningPC->EquippableRenderRef) {
		if (ItemRef) {
			OwningPC->EquippableRenderRef->SetNewRenderMesh(ItemRef, ECaptureStates::Equipment);
		} else {
			OwningPC->EquippableRenderRef->SetNewRenderMesh(NULL, ECaptureStates::None);
		}
	}
}

void UDCInventorySlot::UpdateAddedItem(ADCItem* InItem) {
	ItemRef = InItem;
	if (InventoryButton)
	{
		InventoryButton->WidgetStyle.Normal.SetResourceObject(ItemRef->InventoryImage);
		/*
		InventoryButton->WidgetStyle.Hovered.SetResourceObject();
		InventoryButton->WidgetStyle.Pressed.SetResourceObject();
		InventoryButton->WidgetStyle.Disabled.SetResourceObject();
		InventoryButton->WidgetStyle.NormalPadding.SetResourceObject();
		InventoryButton->WidgetStyle.PressedPadding.SetResourceObject();
		*/
	}
}
