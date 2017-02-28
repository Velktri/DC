// Fill out your copyright notice in the Description page of Project Settings.

#include "DC.h"
#include "DCEnemy.h"
#include "DCWeapon.h"
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
	if (LootReference.Num() > 0 && DropPercentage.Num() > 0) {
		if (LootReference.Num() == DropPercentage.Num()) {
			int32 RandomNumber = FMath::RandRange(1, 100);
			LootChoice = NULL;
			for (int32 i = 0; i < DropPercentage.Num(); i++) {
				if (RandomNumber <= DropPercentage[i]) {
					LootChoice = LootReference[i];
					break;
				}
			}
		} else {
			UE_LOG(LogTemp, Warning, TEXT("Loot Reference and Drop Percentage mismatch error."));
		}
	}
}

void ADCEnemy::OnDeath() {
	FVector DeathLoc = GetActorLocation();
	DeathLoc.Z -= 90.0f;
	FRotator DeathRot = GetActorRotation();
	ADCLoot* LootSpawn = GetWorld()->SpawnActor<ADCLoot>(LootBag, DeathLoc, DeathRot);
	LootSpawn->LootContents = LootChoice;
	
	// destroy enemy and animations
	this->Destroy();
}

void ADCEnemy::EnemyTakeDamage(int32 Damage) {
	Health -= Damage;
	UE_LOG(LogTemp, Warning, TEXT("%s Health: %d"), *Name, Health);

	if (Health <= 0) {
		UE_LOG(LogTemp, Warning, TEXT("%s is Dead"), *Name);
		OnDeath();
	}
}