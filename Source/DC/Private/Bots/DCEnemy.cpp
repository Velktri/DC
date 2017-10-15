// Fill out your copyright notice in the Description page of Project Settings.

#include "DC.h"
#include "DCEnemy.h"
#include "DCEquippable.h"
#include "DCLoot.h"
#include "DCEnemyAIController.h"

// Sets default values
ADCEnemy::ADCEnemy() {
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AIControllerClass = ADCEnemyAIController::StaticClass();
}

// Called when the game starts or when spawned
void ADCEnemy::BeginPlay() {
	Super::BeginPlay();
	SpawnLoot();
}

// Called every frame
void ADCEnemy::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ADCEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ADCEnemy::SpawnLoot() {
	TArray<TSubclassOf<ADCItem>> lootArray;
	Items.GenerateKeyArray(lootArray);
	int32 NumItems = lootArray.Num();
	for (int32 i = 0; i < NumItems; i++) {
		if ((FMath::RandRange(0, 100)) <= Items[lootArray[i]]) {
			SpawnedLoot.Add(lootArray[i]);
		}
	}
}

void ADCEnemy::OnDeath() {
	if (LootBag) {
		FVector loc = FVector(-1570, -260, 410);
		ADCLoot* LootSpawn = GetWorld()->SpawnActor<ADCLoot>(LootBag, loc/*GetActorLocation()*/, GetActorRotation());

		if (LootSpawn) {
			LootSpawn->LootContents = SpawnedLoot;
		}
	}


	// destroy enemy and animations
	Destroy();
}

void ADCEnemy::EnemyTakeDamage(int32 Damage) {
	Health -= Damage;
	UE_LOG(LogTemp, Warning, TEXT("%s Health: %d"), *Name, Health);

	if (Health <= 0) {
		UE_LOG(LogTemp, Warning, TEXT("%s is Dead"), *Name);
		OnDeath();
	}
}