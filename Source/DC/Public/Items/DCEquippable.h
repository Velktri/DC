// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DCItem.h"
#include "DCTypes.h"
#include "DCEquippable.generated.h"

/**
 * 
 */
UCLASS()
class DC_API ADCEquippable : public ADCItem
{
	GENERATED_BODY()

public:

	ADCEquippable();

	/** What happens when an item is unequipped */
	void OnUnEquip();

	/** What happens when an item is equipped */
	virtual void OnEquip();

	/** Attach the Equippable to the player */
	void AttachToPlayer();

	/** Detach the current Equippable from the player */
	void DetachFromPlayer();

	/*  GETTERS  */
	ESlotType GetSlotType();
	USkeletalMeshComponent* GetEquippableMesh();
	UParticleSystemComponent* GetParticleSystem();

protected:

	/** Equippable Mesh */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Config)
	USkeletalMeshComponent* EquippableMesh;

	/** Socket to Equip */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	FName EquipSocket;

	/** Item's Stats */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	FEquipmentStats ItemStats;

	/* Weapon's Equipment Slot */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	ESlotType SlotType;

	/** Particle components for Equippable meshes */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	UParticleSystemComponent* ParticleSystem;
};
