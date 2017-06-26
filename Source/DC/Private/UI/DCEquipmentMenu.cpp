// Fill out your copyright notice in the Description page of Project Settings.

#include "DC.h"
#include "PanelWidget.h"
#include "DCEquippable.h"
#include "DCEquipmentMenu.h"
#include "DCEquipmentSlot.h"
#include "DCPlayerController.h"

UDCGameUIWidget* UDCEquipmentMenu::GenerateEquipSlot(ESlotType EquipSlot, ADCEquippable* Selection) {
	if (OwningPC && Selection && Selection->SlotType == EquipSlot) {
		UDCGameUIWidget* ChildWidget = CreateWidget<UDCGameUIWidget>(OwningPC, EquipmentSlotClass);
		if (ChildWidget) {
			EquipmentSlotContainer->AddChild(ChildWidget);
			return ChildWidget;
		}
	}
	return NULL;
}

void UDCEquipmentMenu::SetFilter(ESlotType InType) {
	ClearFilter();
	if (OwningPC) {
		for (auto& item : OwningPC->Inventory) {
			ADCEquippable* EquipItem = Cast<ADCEquippable>(item);
			if (EquipItem)
			{
				UDCGameUIWidget* widget = GenerateEquipSlot(InType, EquipItem);
				if (widget)
				{
					Cast<UDCEquipmentSlot>(widget)->EquipmentRef = EquipItem;
				}

			}
		}
	}
}

void UDCEquipmentMenu::ClearFilter() {
	if (EquipmentSlotContainer) { EquipmentSlotContainer->ClearChildren(); }
}

