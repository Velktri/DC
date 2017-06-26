// Fill out your copyright notice in the Description page of Project Settings.

#include "DC.h"
#include "DCEquipmentSlot.h"
#include "DCEquippable.h"
#include "DCPlayerController.h"
#include "UI_Render.h"

void UDCEquipmentSlot::SelectEquipment(ADCEquippable* EquipmentItem) {
	if (OwningPC) { OwningPC->EquipEquippable(EquipmentItem); }
}

void UDCEquipmentSlot::ItemClick() {
	if (OwningPC && OwningPC->EquippableRenderRef) {
		if (EquipmentRef) {
			SelectEquipment(EquipmentRef);
			OwningPC->EquippableRenderRef->AppendEquipmentToRender();
		} else {
			OwningPC->EquippableRenderRef->AppendEquipmentToRender();
		}
	}
}
