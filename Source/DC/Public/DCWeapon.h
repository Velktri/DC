// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DCItem.h"
#include "DCWeapon.generated.h"

/**
 * 
 */
UCLASS()
class DC_API ADCWeapon : public ADCItem
{
	GENERATED_BODY()

public:

	ADCWeapon();
	/** Stats */
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
	
	void OnUnEquip();

	/** What happens when an item is equipped */
	void OnEquip();

	/** Attach the weapon to the player */
	void AttachToPlayer();

	/** Detach the current weapon from the player */
	void DetachFromPlayer();

	/** Weapon Mesh */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Config)
	USkeletalMeshComponent* SwordMesh;

	/** Weapon Collision Box */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision)
	UBoxComponent* CollisionComp;

	/** Particle components for weapon meshes */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particles")
	UParticleSystemComponent* OurParticleSystem;

	/** Animation played on pawn */
	UPROPERTY(EditDefaultsOnly, Category = Animation)
	UAnimMontage* MeshAnim;

	UBoxComponent* GetCollisionComp();

	UFUNCTION()
	void OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
};
