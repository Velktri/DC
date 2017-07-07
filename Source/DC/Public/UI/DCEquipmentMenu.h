// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DCTypes.h"
#include "UI/DCGameUIWidget.h"
#include "DCEquipmentMenu.generated.h"

/**
 * 
 */
UCLASS()
class DC_API UDCEquipmentMenu : public UDCGameUIWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	TSubclassOf<UUserWidget> EquipmentSlotClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	class UPanelWidget* EquipmentSlotContainer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	uint8 ActiveEquipmentFilter;

	UFUNCTION(BlueprintCallable, Category = Config)
	UDCGameUIWidget* GenerateEquipSlot(ESlotType EquipSlot, ADCEquippable* Selection);

	UFUNCTION(BlueprintCallable, Category = Config)
	void SetFilter(ESlotType InType);

	UFUNCTION(BlueprintCallable, Category = Config)
	void ChangeFilter(bool LeftPressed);

	UFUNCTION(BlueprintCallable, Category = Config)
	void ClearFilter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	class UTextBlock* ItemName;
};
