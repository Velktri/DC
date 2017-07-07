// Fill out your copyright notice in the Description page of Project Settings.

#include "DC.h"
#include "TextBlock.h"
#include "DCEquipmentSlot.h"
#include "DCEquipmentMenu.h"
#include "DCEquippable.h"
#include "DCPlayerController.h"
#include "UI_Render.h"

void UDCEquipmentSlot::SelectEquipment(ADCEquippable* EquipmentItem) {
	if (OwningPC) { OwningPC->EquipEquippable(EquipmentItem); }
}

void UDCEquipmentSlot::ItemClick() {
	if (OwningPC && OwningPC->GetUI_RenderRef()) 
	{
		if (EquipmentRef) 
		{
			SelectEquipment(EquipmentRef);
			OwningPC->GetUI_RenderRef()->AppendEquipmentToRender(EquipmentRef);
			SetDetails(EquipmentRef);
		}
	}
}

void UDCEquipmentSlot::SetDetails(ADCEquippable* InItem) {
	if (InItem) {
		OwnerMenu->ItemName->SetText(InItem->GetItemName());
	}
}
