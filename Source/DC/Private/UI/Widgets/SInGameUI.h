// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class SInGameUI : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SInGameUI)
	{}
	SLATE_ARGUMENT(TWeakObjectPtr<class ADCHUD>, DCHUD)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	// Stores a weak reference to the HUD controlling this class.
	TWeakObjectPtr<class ADCHUD> DCHUD;

private:
	TOptional<float> GetHealthPercent() const;
	TOptional<float> GetEnergyPercent() const;

	FSlateBrush CharacterRenderImage;
};
