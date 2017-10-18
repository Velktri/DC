// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "DCTypes.h"
#include "DCPlayerController.generated.h"

class ADCEquippable;
class UDCGameUIWidget;
class ADCMeleeWeapon;
class ADCArmor;
class AUI_Render;

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
	
	/** Show StartMenu */
	UFUNCTION()
	void PauseGame();

	/** Hide StartMenu */
	UFUNCTION(BlueprintCallable)
	void ResumeGame();

	/** Allows the PlayerController to set up custom input bindings. */
	virtual void SetupInputComponent() override;

	/** Equip item to slot */
	UFUNCTION()
	void EquipEquippable(ADCEquippable* InItem);

	/** Equipment Helper */
	template< class T >
	void EquipToSlot(ADCEquippable* InItem);

	/** Add item to Inventory */
	UFUNCTION()
	void AddToInventory(class ADCItem* InItem);

	/** Generate Menu */
	UFUNCTION()
	void CreatePlayerWidgets();

	/* GETTERS */
	UFUNCTION()
	TArray<class ADCItem*> GetInventory();

	UFUNCTION()
	UDCGameUIWidget* GetStartMenuWidget();

	UFUNCTION()
	AUI_Render* GetUI_RenderRef();

	UFUNCTION()
	TMap<ESlotType, ADCEquippable*> GetCurrentEquipment();

protected:

	/** Inventory for the Character. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Config | Inventory")
	TArray<class ADCItem*> Inventory;

	/** Max Inventory size for the Character */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config | Inventory")
	int32 MaxInventorySize;

	/** Current Equipment the character is holding. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Config | Inventory")
	TMap<ESlotType, ADCEquippable*> CurrentEquipment;

	/** Widget class for Start Menu */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config | UI")
	TSubclassOf<class UUserWidget> StartMenuClass;

	/** Widget instance for Start Menu */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Config | UI")
	UDCGameUIWidget* StartMenuWidget;

	/** Pause state of the Game */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Config | UI")
	bool bIsPaused;

	/** UI Render Reference */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Config | UI")
	AUI_Render* EquippableRenderRef;

	/** UI Render class */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config | Classes")
	TSubclassOf<class AActor> EquippableRenderClass;
};
