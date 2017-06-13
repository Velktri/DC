// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "DCPlayerController.generated.h"

class ADCEquippable;
class UDCGameUIWidget;
class ADCMeleeWeapon;
class ADCArmor;

USTRUCT()
struct FEquipmentSet {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment | Weapon")
	ADCMeleeWeapon* RightWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment | Weapon")
	ADCMeleeWeapon* LeftWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment | Weapon")
	class ADCShield* Shield;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment | Weapon")
	class ADCRangedWeapon* RangedWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment | Armor")
	ADCArmor* Head;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment | Armor")
	ADCArmor* Shoulder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment | Armor")
	ADCArmor* Chest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment | Armor")
	ADCArmor* Legs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment | Armor")
	ADCArmor* Boots;

	FEquipmentSet() {
		RightWeapon		= NULL;
		LeftWeapon		= NULL;
		Shield			= NULL;
		RangedWeapon	= NULL;
		Head			= NULL;
		Shoulder		= NULL;
		Chest			= NULL;
		Legs			= NULL;
		Boots			= NULL;
	}
};

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
	UDCGameUIWidget* GetInGameWidget();

	UFUNCTION()
	UDCGameUIWidget* GetStartMenuWidget();

	UFUNCTION()
	void EquipEquippable(ADCItem* InItem);

	/** Widget for InGame HUD */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	class UDCGameUIWidget* InGameUI;

	/** Widget for Start Menu */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	class UDCGameUIWidget* StartMenuWidget;

	/** Current Equipment the character is holding. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory)
	FEquipmentSet CurrentEquipment;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI)
	bool bIsPaused;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI)
	class AUI_Render* EquippableRenderRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Classes)
	TSubclassOf<class AActor> EquippableRenderClass;
};
