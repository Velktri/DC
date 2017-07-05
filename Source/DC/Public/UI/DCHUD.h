// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DCHUD.generated.h"

/**
 * 
 */
UCLASS()
class DC_API ADCHUD : public AHUD
{
	GENERATED_BODY()

	ADCHUD();

	// Initializes the Slate UI and adds it as widget content to the game viewport.
	virtual void PostInitializeComponents() override;

	// Reference to the Main Menu Slate UI.
	TSharedPtr<class SInGameUI> InGameUI;

public:
	UMaterial* GetCharacterRenderImage();

	void ToggleHUD();

protected:
	UPROPERTY(EditAnywhere, Category = Config)
	UMaterial* CharacterRenderImage;

private:
	bool bHUDVisible;
};
