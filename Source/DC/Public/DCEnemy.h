// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "DCEnemy.generated.h"

UCLASS()
class DC_API ADCEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADCEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Enemy's AI class */
	UPROPERTY(EditAnywhere, Category = Behavior)
	class UBehaviorTree* BotBehavior;

	/** Enemy Sight Distance. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Behavior)
	int32 SightDistance;

	/** Current health of the Enemy. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	int32 Health;

	/** Current health of the Enemy. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Name)
	FString Name;

	/** All Loot that can drop. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Loot)
	TArray<TSubclassOf<class ADCItem>> LootReference;

	/**  Drop percentage for the loot reference. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Loot)
	TArray<int32> DropPercentage;

	/** The Enemy's Loot Reference. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Loot)
	TSubclassOf<class ADCItem> LootChoice;

	/** Select Loot */
	void SpawnLoot();

	/** Loot class that drops when enemy dies. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Loot)
	TSubclassOf<class ADCLoot> LootBag;

	UFUNCTION()
	void OnDeath();

	UFUNCTION()
	void EnemyTakeDamage(int32 Damage);
};
