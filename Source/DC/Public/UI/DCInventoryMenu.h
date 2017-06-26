// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/DCGameUIWidget.h"
#include "DCInventoryMenu.generated.h"

/**
 * 
 */
UCLASS()
class DC_API UDCInventoryMenu : public UDCGameUIWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	TSubclassOf<UUserWidget> InventorySlotClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	class UUniformGridPanel* InventoryContents;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	int InventoryPanelWidth;

	UFUNCTION(BlueprintCallable, Category = "Config")
	void InitInventory();

	UFUNCTION(BlueprintCallable, Category = "Config")
	void TickFunc(float DeltaTime);
};
