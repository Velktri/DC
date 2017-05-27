// Fill out your copyright notice in the Description page of Project Settings.

#include "DC.h"
#include "DCGameUIWidget.h"
#include "DCItem.h"
#include "DCPlayerController.h"


void UDCGameUIWidget::AddInventoryItem(class ADCItem* Item) {
	UpdateInventory(Item);
}

void UDCGameUIWidget::SelectItem(ADCItem* Selection) {
	AController* PC = GetOwningPlayer();
	if (PC) {
		Cast<ADCPlayerController>(PC)->EquipWeapon(Selection);
	}
}
