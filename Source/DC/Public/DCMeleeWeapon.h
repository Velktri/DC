// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DCEquippable.h"
#include "DCMeleeWeapon.generated.h"

/**
 * 
 */
UCLASS()
class DC_API ADCMeleeWeapon : public ADCEquippable
{
	GENERATED_BODY()
	
public:
	ADCMeleeWeapon();
	
	/** What happens when an item is equipped */
	virtual void OnEquip() override;

	/** Equippable Collision Box */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision)
	UBoxComponent* CollisionComp;

	UBoxComponent* GetCollisionComp();

	UFUNCTION()
	void OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
};
