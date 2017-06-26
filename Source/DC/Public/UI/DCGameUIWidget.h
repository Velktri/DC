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

	UFUNCTION(BlueprintImplementableEvent, Category = "Config")
	void UpdateInventory(class ADCItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Config")
	void SetDCPlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	class ADCPlayerController* OwningPC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	class UDCGameUIWidget* PrimaryFocusWidget;
};