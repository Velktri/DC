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
#include "Button.h"
#include "WidgetAnimation.h"
#include "EngineUtils.h"

void UDCStartMenu::B_Pressed() {
	if (OwningPC) {
		OwningPC->ResumeGame();
		if (OwningPC->EquippableRenderRef) {
			Cast<AUI_Render>(OwningPC->EquippableRenderRef)->SetNewRenderMesh(OwningPC->GetPawn(), ECaptureStates::InGame);
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
				Cast<AUI_Render>(OwningPC->EquippableRenderRef)->SetNewRenderMesh(OwningPC->GetPawn(), ECaptureStates::Character);	
			}
			break;
		case 1:
			if (OwningPC) 
			{
				Cast<AUI_Render>(OwningPC->EquippableRenderRef)->SetNewRenderMesh(OwningPC->GetPawn(), ECaptureStates::Character);
			}
			break;
		case 2:
			if (OwningPC && InventoryMenu && InventoryMenu->PrimaryFocusWidget)
			{
				UDCInventorySlot* InvSlot = Cast<UDCInventorySlot>(InventoryMenu->PrimaryFocusWidget);
				if (InvSlot && OwningPC->EquippableRenderRef)
				{
					OwningPC->EquippableRenderRef->SetNewRenderMesh(InvSlot->ItemRef, ECaptureStates::Equipment);
				} 
				else 
				{
					OwningPC->EquippableRenderRef->SetNewRenderMesh(NULL, ECaptureStates::None);
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
		if (InWidget->IsA(UDCEquipmentMenu::StaticClass()))
		{
			UButton* DCEquipWidget = Cast<UDCEquipmentMenu>(InWidget)->FocusButton;
			if (DCEquipWidget) {
				DCEquipWidget->SetUserFocus(OwningPC);
			}
		} 
		else if (InWidget->IsA(UDCGameUIWidget::StaticClass()))
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
		if (InKey == EKeys::Gamepad_FaceButton_Right)
		{
			B_Pressed();
		} 
		else if (InKey == EKeys::Gamepad_FaceButton_Top)
		{
			Y_Pressed();
		}
		else if (InKey == EKeys::Gamepad_LeftShoulder) 
		{
			bIsBlockingInput = true;
			Shoulder_Pressed_Event(true);
		}
		else if (InKey == EKeys::Gamepad_RightShoulder)
		{
			bIsBlockingInput = true;
			Shoulder_Pressed_Event(false);
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
