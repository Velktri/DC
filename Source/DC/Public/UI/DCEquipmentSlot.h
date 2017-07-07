// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/DCGameUIWidget.h"
#include "DCEquipmentSlot.generated.h"

/**
 * 
 */
UCLASS()
class DC_API UDCEquipmentSlot : public UDCGameUIWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	class ADCEquippable* EquipmentRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	class UDCEquipmentMenu* OwnerMenu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	class UButton* InventoryButton;

	UFUNCTION(BlueprintCallable, Category = Config)
	void SelectEquipment(class ADCEquippable* EquipmentItem);
	
	UFUNCTION(BlueprintCallable, Category = Config)
	void ItemClick();
	
	UFUNCTION(BlueprintCallable, Category = Config)
	void SetDetails(ADCEquippable* InItem);
};
