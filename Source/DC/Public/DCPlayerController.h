// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "DCPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DC_API ADCPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	ADCPlayerController();

	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

	/** Inventory for the Character. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory)
	TArray<class ADCItem*> Inventory;
	
	/** Max Inventory size for the Character */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inventory)
	int32 MaxInventorySize;

	/** Print the current inventory */
	UFUNCTION()
	void PrintInventory();

	/* Show or Hide StartMenu */
	UFUNCTION()
	void PauseGame();

	UFUNCTION(BlueprintCallable, Category = "Item")
	void ResumeGame();

	/** Allows the PlayerController to set up custom input bindings. */
	virtual void SetupInputComponent() override;

	UFUNCTION()
	TArray<class ADCItem*> GetInventory();

	UFUNCTION()
	void AddToInventory(class ADCItem* InItem);

	UFUNCTION()
	class UDCGameUIWidget* GetInGameWidget();

	UFUNCTION()
	class UDCGameUIWidget* GetStartMenuWidget();

	UFUNCTION()
	void EquipWeapon(ADCItem* InItem);

	/** Widget for InGame HUD */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	class UDCGameUIWidget* InGameUI;

	/** Widget for Start Menu */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	class UDCGameUIWidget* StartMenuWidget;

	/** Current Weapon the character is holding. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory)
	class ADCWeapon* CurrentWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI)
	bool bIsPaused;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI)
	class AActor* WeaponRenderRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Classes)
	TSubclassOf<class AActor> WeaponRenderClass;
};
