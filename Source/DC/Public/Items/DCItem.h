// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DCItem.generated.h"

class ADCCharacter;

UCLASS()
class DC_API ADCItem : public AActor
{
	GENERATED_BODY()
	
public:	
	ADCItem();

	/** Returns the name of the item */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	UTexture* InventoryImage;

	/** Animation to play in the Start Menu. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimationAsset* UI_Animation;

	/** Get Weapon Name */
	FString GetItemName();

	/** Sets the item's owner */
	void SetPlayerController(class ADCPlayerController* NewOwner);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Pawn owner */
	class ADCPlayerController* MyOwner;
};
