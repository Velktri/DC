// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DCItem.h"
#include "DCEquippable.generated.h"

USTRUCT()
struct FEquipmentStats {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	int32 Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	int32 Fire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	int32 Ice;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	int32 Wind;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	int32 Earth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	int32 Light;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	int32 Dark;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	int32 Haste;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	int32 Critical;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	int32 Experience;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	int32 Level;

	FEquipmentStats() {
		Attack		= 0;
		Fire		= 0;
		Ice			= 0;
		Wind		= 0;
		Earth		= 0;
		Light		= 0;
		Dark		= 0;
		Haste		= 0;
		Critical	= 0;
		Experience	= 0;
		Level		= 1;
	}
};

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

	/** Equippable Mesh */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Config)
	USkeletalMeshComponent* EquippableMesh;

	/** Socket to Equip */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	FName EquipSocket;

	/** Item's Stats */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	FEquipmentStats ItemStats;

	/** Particle components for Equippable meshes */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particles")
	UParticleSystemComponent* OurParticleSystem;
};
