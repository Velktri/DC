// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DCChest.generated.h"

UCLASS()
class DC_API ADCChest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADCChest();

	/** The loot inside the loot bag */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loot")
	TArray<TSubclassOf<class ADCItem>> ChestItems;

	TArray<TSubclassOf<class ADCItem>> GetLootContents();
	UBoxComponent* GetTrigger();

	/* Called when the chest is looted by a player. */

	UFUNCTION()
	void LootChest();
	
protected:
	/** Chest Mesh */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* ChestMesh;

	/** Loot Mesh */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Loot")
	UBoxComponent* OpeningTrigger;

	UFUNCTION()
	void EnterCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION()
	void LeaveCollision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bIsLocked;
};
