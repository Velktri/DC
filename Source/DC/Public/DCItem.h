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
	// Sets default values for this actor's properties
	ADCItem();

	/** Returns the name of the item */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	FString ItemName;

	/** Get Weapon Name */
	FString GetItemName();

	/** Sets the item's owner */
	void SetOwningPawn(ADCCharacter* NewOwner);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Pawn owner */
	class ADCCharacter* MyPawn;
};
