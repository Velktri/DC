// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/DCGameUIWidget.h"
#include "DCInventorySlot.generated.h"

/**
 * 
 */
UCLASS()
class DC_API UDCInventorySlot : public UDCGameUIWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	class ADCItem* ItemRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	class UButton* InventoryButton;

	
	UFUNCTION(BlueprintCallable, Category = "Config")
	void ItemClick();

	UFUNCTION(BlueprintCallable, Category = "Config")
	void UpdateAddedItem(ADCItem* InItem);
};
