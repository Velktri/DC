// Fill out your copyright notice in the Description page of Project Settings.

#include "DC.h"
#include "DCGameUIWidget.h"
#include "DCPlayerController.h"

void UDCGameUIWidget::AddInventoryItem(class ADCItem* Item) {
	UpdateInventory(Item);
}

void UDCGameUIWidget::SetDCPlayerController() {
	if (!OwningPC) { OwningPC = Cast<ADCPlayerController>(GetOwningPlayer()); }
}