// Fill out your copyright notice in the Description page of Project Settings.

#include "DC.h"
#include "DCGameUIWidget.h"
#include "DCEquippable.h"
#include "PanelWidget.h"
#include "DCPlayerController.h"

void UDCGameUIWidget::AddInventoryItem(class ADCItem* Item) {
	UpdateInventory(Item);
}

void UDCGameUIWidget::GenerateEquipSlot(TSubclassOf<UUserWidget> ChildWidgetClass, UPanelWidget* ParentWidget, ESlotType EquipSlot, ADCItem* Selection, UDCGameUIWidget*& ChildWidget, ADCEquippable*& EquipSelection) {
	if (Selection && OwningPC)
	{
		EquipSelection = Cast<ADCEquippable>(Selection);
		if (EquipSelection && EquipSelection->SlotType == EquipSlot) {
			ChildWidget = CreateWidget<UDCGameUIWidget>(OwningPC, ChildWidgetClass);
			if (ChildWidget) { ParentWidget->AddChild(ChildWidget); }
		}
	}
}

void UDCGameUIWidget::SelectItem(ADCItem* Selection) {
	//if (OwningPC) { OwningPC->EquipEquippable(Selection); }
}

void UDCGameUIWidget::SelectEquipment(ADCEquippable* EquipmentItem) {
	if (OwningPC) { OwningPC->EquipEquippable(EquipmentItem); }
}

void UDCGameUIWidget::SetDCPlayerController() {
	if (!OwningPC) { OwningPC = Cast<ADCPlayerController>(GetOwningPlayer()); }
}