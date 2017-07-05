// Fill out your copyright notice in the Description page of Project Settings.

#include "DC.h"
#include "DCHUD.h"
#include "Widgets/SInGameUI.h"
#include "Engine.h"

ADCHUD::ADCHUD() {
	static ConstructorHelpers::FObjectFinder<UMaterial> CharacterRenderImageObj(TEXT("/Game/UI/Scene_Capture/UI_RenderView.UI_RenderView"));


	CharacterRenderImage = CharacterRenderImageObj.Object;

	bHUDVisible = true;
}

void ADCHUD::PostInitializeComponents() {
	Super::PostInitializeComponents();

	SAssignNew(InGameUI, SInGameUI).DCHUD(this);

	if (GEngine->IsValidLowLevel()) {
		GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(InGameUI.ToSharedRef()));
	}
}

UMaterial* ADCHUD::GetCharacterRenderImage() {
	return CharacterRenderImage;
}

void ADCHUD::ToggleHUD() {
	bHUDVisible = !bHUDVisible;
	InGameUI->SetVisibility((bHUDVisible) ? EVisibility::Visible : EVisibility::Collapsed);
}
