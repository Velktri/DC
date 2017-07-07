// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/DCGameUIWidget.h"
#include "DCStartMenu.generated.h"

/**
 * 
 */
UCLASS()
class DC_API UDCStartMenu : public UDCGameUIWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	class UWidgetSwitcher* PanelSwitcher;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	class UDCInventoryMenu* InventoryMenu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	class UDCEquipmentMenu* EquipmentMenu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	class UWidgetAnimation* SwitcherAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	int ActiveMenuIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	bool bIsBlockingInput;

	UFUNCTION(BlueprintCallable, Category = Config)
	void B_Pressed();

	UFUNCTION(BlueprintCallable, Category = Config)
	void Y_Pressed();

	UFUNCTION(BlueprintCallable, Category = Config)
	void InitStartMenu();

	UFUNCTION(BlueprintCallable, Category = Config)
	void InitCurrentRenderTarget();

	UFUNCTION(BlueprintCallable, Category = Config)
	void SetWidgetFocus(class UWidget* InWidget);

	UFUNCTION(BlueprintCallable, Category = Config)
	void DetermineKeyEvent(FKey InKey);
	
	UFUNCTION(BlueprintCallable, Category = Config)
	float Shoulder_Pressed(bool LeftPressed);

	UFUNCTION(BlueprintCallable, Category = Config)
	void Shoulder(bool LeftPressed);

	UFUNCTION(BlueprintCallable, Category = Config)
	void GamepadRightThumbstick(bool LeftPressed);

	UFUNCTION(BlueprintImplementableEvent, Category = "Config")
	void Shoulder_Pressed_Event(bool LeftPressed);
};
