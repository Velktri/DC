// Fill out your copyright notice in the Description page of Project Settings.

#include "DC.h"
#include "DCEquippable.h"
#include "DCEquipmentMenu.h"
#include "DCEquipmentSlot.h"
#include "DCPlayerController.h"
#include "Engine.h"
#include "PanelWidget.h"

UDCGameUIWidget* UDCEquipmentMenu::GenerateEquipSlot(ESlotType EquipSlot, ADCEquippable* Selection) {
	if (OwningPC && Selection && Selection->GetSlotType() == EquipSlot) {
		UDCEquipmentSlot* ChildWidget = CreateWidget<UDCEquipmentSlot>(OwningPC, EquipmentSlotClass);
		if (ChildWidget) {
			EquipmentSlotContainer->AddChild(ChildWidget);
			ChildWidget->OwnerMenu = this;
			return ChildWidget;
		}
	}
	return NULL;
}

void UDCEquipmentMenu::SetFilter(ESlotType InType) {
	ClearFilter();
	if (OwningPC) {
		for (auto& item : OwningPC->GetInventory()) {
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

		if (EquipmentSlotContainer->HasAnyChildren())
		{
			PrimaryFocusWidget = Cast<UDCGameUIWidget>(EquipmentSlotContainer->GetChildAt(0));
			PrimaryFocusWidget->SetUserFocus(OwningPC);
		}
	}
}

void UDCEquipmentMenu::ChangeFilter(bool LeftPressed) {
	if (LeftPressed && ActiveEquipmentFilter > 0) 
	{
		ActiveEquipmentFilter--;
		SetFilter(static_cast<ESlotType>(ActiveEquipmentFilter));
	} 
	else if (!LeftPressed && ActiveEquipmentFilter < 7) 
	{
		ActiveEquipmentFilter++;
		SetFilter(static_cast<ESlotType>(ActiveEquipmentFilter));
	}

	// change old image to show not highlighted
	// change image colors to show highlighted
}

void UDCEquipmentMenu::ClearFilter() {
	if (EquipmentSlotContainer) { EquipmentSlotContainer->ClearChildren(); }
}
