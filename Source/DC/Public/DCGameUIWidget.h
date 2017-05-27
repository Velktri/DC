// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
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

	UFUNCTION(BlueprintImplementableEvent, Category = "Item")
	void UpdateInventory(class ADCItem* Item);
	
	UFUNCTION(BlueprintCallable, Category = "Item")
	void SelectItem(ADCItem* Selection);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	class ADCPlayerController* OwningPC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	class UDCGameUIWidget* PrimaryFocusWidget;
};
