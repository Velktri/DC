// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "DCTypes.h"
#include "DCGameUIWidget.generated.h"

/**
 * 
 */
UCLASS()
class DC_API UDCGameUIWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void AddInventoryItem(class ADCItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Item")
	void GenerateEquipSlot(TSubclassOf<UUserWidget> ChildWidgetClass, class UPanelWidget* ParentWidget, ESlotType EquipSlot, ADCItem* Selection, UDCGameUIWidget*& ChildWidget, ADCEquippable*& EquipSelection);

	UFUNCTION(BlueprintImplementableEvent, Category = "Item")
	void UpdateInventory(class ADCItem* Item);
	
	UFUNCTION(BlueprintCallable, Category = "Item")
	void SelectItem(ADCItem* Selection);

	UFUNCTION(BlueprintCallable, Category = "Item")
	void SelectEquipment(class ADCEquippable* EquipmentItem);

	UFUNCTION(BlueprintCallable)
	void SetDCPlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	class ADCPlayerController* OwningPC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	class UDCGameUIWidget* PrimaryFocusWidget;
};