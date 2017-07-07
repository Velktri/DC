// Fill out your copyright notice in the Description page of Project Settings.

#include "DC.h"
#include "DCStartMenu.h"
#include "DCPlayerController.h"
#include "UI_Render.h"
#include "WidgetSwitcher.h"
#include "DCEquipmentMenu.h"
#include "DCInventoryMenu.h"
#include "DCInventorySlot.h"
#include "DCItem.h"
#include "ScrollBox.h"
#include "WidgetAnimation.h"
#include "EngineUtils.h"
#include "Engine.h"

void UDCStartMenu::B_Pressed() {
	if (OwningPC) {
		OwningPC->ResumeGame();
		if (OwningPC->GetUI_RenderRef()) {
			Cast<AUI_Render>(OwningPC->GetUI_RenderRef())->SetNewRenderMesh(OwningPC->GetPawn(), ECaptureStates::InGame);
		}
	}
}

void UDCStartMenu::Y_Pressed() {

}

void UDCStartMenu::InitStartMenu() {
	if (OwningPC && PanelSwitcher) {
		FInputModeUIOnly inputType;
		inputType.SetWidgetToFocus(PanelSwitcher->GetWidgetAtIndex(PanelSwitcher->GetActiveWidgetIndex())->TakeWidget());
		OwningPC->SetInputMode(inputType);
		ActiveMenuIndex = PanelSwitcher->GetActiveWidgetIndex();
		InitCurrentRenderTarget();
		bIsBlockingInput = false;
		SetWidgetFocus(PanelSwitcher->GetWidgetAtIndex(PanelSwitcher->GetActiveWidgetIndex()));
	}
}

void UDCStartMenu::InitCurrentRenderTarget() {
	switch (ActiveMenuIndex)
	{
		case 0:
			if (OwningPC)
			{
				Cast<AUI_Render>(OwningPC->GetUI_RenderRef())->SetNewRenderMesh(OwningPC->GetPawn(), ECaptureStates::Character);	
			}
			break;
		case 1:
			if (OwningPC) 
			{
				Cast<AUI_Render>(OwningPC->GetUI_RenderRef())->SetNewRenderMesh(OwningPC->GetPawn(), ECaptureStates::Character);
			}
			break;
		case 2:
			if (OwningPC && InventoryMenu && InventoryMenu->PrimaryFocusWidget)
			{
				UDCInventorySlot* InvSlot = Cast<UDCInventorySlot>(InventoryMenu->PrimaryFocusWidget);
				if (InvSlot && OwningPC->GetUI_RenderRef())
				{
					OwningPC->GetUI_RenderRef()->SetNewRenderMesh(InvSlot->ItemRef, ECaptureStates::Equipment);
				} 
				else 
				{
					OwningPC->GetUI_RenderRef()->SetNewRenderMesh(NULL, ECaptureStates::None);
				}
			}
			break;
		case 3:

			break;
		case 4:

			break;
		default:
			break;
	}	
}

void UDCStartMenu::SetWidgetFocus(UWidget* InWidget) {
	if (InWidget)
	{
		if (InWidget->IsA(UDCGameUIWidget::StaticClass()))
		{
			UDCGameUIWidget* DCWidget = Cast<UDCGameUIWidget>(InWidget)->PrimaryFocusWidget;
			if (DCWidget) {
				DCWidget->SetUserFocus(OwningPC);
			}
		}
	}
}

void UDCStartMenu::DetermineKeyEvent(FKey InKey) {
	if (!bIsBlockingInput)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FText(InKey.GetDisplayName()).ToString());
		if (InKey == EKeys::Gamepad_FaceButton_Right)
		{
			B_Pressed();
		} 
		else if (InKey == EKeys::Gamepad_FaceButton_Top)
		{
			Y_Pressed();
		}
		else if (InKey == EKeys::Gamepad_LeftShoulder || InKey == EKeys::Gamepad_RightShoulder)
		{
			bIsBlockingInput = true;
			Shoulder_Pressed_Event((InKey == EKeys::Gamepad_LeftShoulder) ? true : false);
		}
		else if (InKey == EKeys::Gamepad_RightStick_Right || InKey == EKeys::Gamepad_RightStick_Left)
		{
			GamepadRightThumbstick((InKey == EKeys::Gamepad_RightStick_Left) ? true : false);
		}
	}
}

float UDCStartMenu::Shoulder_Pressed(bool LeftPressed) {
	float AnimationTime = SwitcherAnimation->GetEndTime() / 2;
	if (LeftPressed && ActiveMenuIndex > 0)
	{
		PlayAnimation(SwitcherAnimation);
	} 
	else if (!LeftPressed && (ActiveMenuIndex + 1) < PanelSwitcher->GetNumWidgets())
	{
		PlayAnimation(SwitcherAnimation, 0, 1, EUMGSequencePlayMode::Reverse, 1);
	}
	return AnimationTime;
}

void UDCStartMenu::Shoulder(bool LeftPressed) {
	if (!LeftPressed && (ActiveMenuIndex + 1) < PanelSwitcher->GetNumWidgets()) {
		ActiveMenuIndex++;
		PanelSwitcher->SetActiveWidgetIndex(ActiveMenuIndex);
		SetWidgetFocus(PanelSwitcher->GetWidgetAtIndex(ActiveMenuIndex));
	} 
	else if (LeftPressed && ActiveMenuIndex > 0) 
	{
		ActiveMenuIndex--;
		PanelSwitcher->SetActiveWidgetIndex(ActiveMenuIndex);
		SetWidgetFocus(PanelSwitcher->GetWidgetAtIndex(ActiveMenuIndex));
	}

	InitCurrentRenderTarget();
}

void UDCStartMenu::GamepadRightThumbstick(bool LeftPressed) {
	if (ActiveMenuIndex == 1 && EquipmentMenu)
	{
		EquipmentMenu->ChangeFilter(LeftPressed);
	}
}
