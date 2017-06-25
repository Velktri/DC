// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "DCTypes.h"
#include "DCPlayerController.generated.h"

class ADCEquippable;
class UDCGameUIWidget;
class ADCMeleeWeapon;
class ADCArmor;

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

	/* Show StartMenu */
	UFUNCTION()
	void PauseGame();

	/* Hide StartMenu */
	UFUNCTION(BlueprintCallable, Category = "Item")
	void ResumeGame();

	/** Allows the PlayerController to set up custom input bindings. */
	virtual void SetupInputComponent() override;

	UFUNCTION()
	TArray<class ADCItem*> GetInventory();

	UFUNCTION()
	void AddToInventory(class ADCItem* InItem);

	UFUNCTION()
	void CreatePlayerWidgets();

	UFUNCTION()
	UDCGameUIWidget* GetInGameWidget();

	UFUNCTION()
	UDCGameUIWidget* GetStartMenuWidget();

	UFUNCTION()
	void EquipEquippable(ADCEquippable* InItem);

	template< class T >
	void EquipToSlot(ADCEquippable* InItem);

	/** Widget for InGame HUD */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UUserWidget> InGameClass;

	/** Widget instance for InGame HUD */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI)
	class UDCGameUIWidget* InGameUI;

	/** Widget for Start Menu */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UUserWidget> StartMenuClass;

	/** Widget instance for Start Menu */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI)
	class UDCGameUIWidget* StartMenuWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI)
	bool bIsPaused;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI)
	class AUI_Render* EquippableRenderRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Classes)
	TSubclassOf<class AActor> EquippableRenderClass;

	/** Current Equipment the character is holding. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory)
	TMap<ESlotType, ADCEquippable*> CurrentEquipment;
};
