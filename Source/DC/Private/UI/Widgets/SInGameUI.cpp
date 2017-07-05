// Fill out your copyright notice in the Description page of Project Settings.

#include "DC.h"
#include "SInGameUI.h"
#include "DCCharacter.h"
#include "DCHUD.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SInGameUI::Construct(const FArguments& InArgs)
{
	DCHUD = InArgs._DCHUD;

	UMaterialInterface* mat = Cast<UMaterialInterface>(DCHUD->GetCharacterRenderImage());
	CharacterRenderImage.SetResourceObject(mat);
	CharacterRenderImage.ImageSize = FVector2D(110, 110);

	ChildSlot
			[
				SNew(SOverlay)
				+ SOverlay::Slot()
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Top)
				[
					// Character Stats
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.Padding(FMargin(100, 100, 0, 0))
					.AutoWidth()
					[
						SNew(SBox)
						.MaxDesiredWidth(110)
						.MaxDesiredHeight(110)
						[
							// Character Image
							SNew(SImage)
							.Image(&CharacterRenderImage)
						]
					]

					+ SHorizontalBox::Slot()
					.Padding(FMargin(0, 100, 0, 0))
					.AutoWidth()
					[
						// Health and Energy Container
						SNew(SVerticalBox)
						+ SVerticalBox::Slot()
						[
							SNew(SBox)
							.MinDesiredWidth(375)
							.MinDesiredHeight(55)
							.MaxDesiredHeight(55)
							[
								// Health
								SNew(SProgressBar)
								.Percent(this, &SInGameUI::GetHealthPercent)
								.FillColorAndOpacity(FLinearColor(0.020165f, 0.235f, 0.0f))
							]
						]

						+ SVerticalBox::Slot()
						[
							SNew(SBox)
							.MinDesiredWidth(375)
							.MinDesiredHeight(55)
							.MaxDesiredHeight(55)
							[
								// Energy
								SNew(SProgressBar)
								.Percent(this, &SInGameUI::GetEnergyPercent)
								.FillColorAndOpacity(FLinearColor(0.029025f, 0.592723f, 0.645f))
							]
						]
					]
				]
			];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

TOptional<float> SInGameUI::GetHealthPercent() const {
	ADCCharacter* character = Cast<ADCCharacter>(DCHUD->PlayerOwner->GetCharacter());
	return (character) ? ((float) character->CurrentHealth / (float) character->Health) : 0.0f;
}

TOptional<float> SInGameUI::GetEnergyPercent() const {
	ADCCharacter* character = Cast<ADCCharacter>(DCHUD->PlayerOwner->GetCharacter());
	return (character) ? ((float)character->CurrentEnergy / (float)character->Energy) : 0.0f;
}