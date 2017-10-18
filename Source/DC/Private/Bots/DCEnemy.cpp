// Fill out your copyright notice in the Description page of Project Settings.

#include "DC.h"
#include "DCEnemy.h"
#include "DCEquippable.h"
#include "DCLoot.h"
#include "DCEnemyAIController.h"

ADCEnemy::ADCEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	AIControllerClass = ADCEnemyAIController::StaticClass();
}

void ADCEnemy::BeginPlay()
{
	Super::BeginPlay();
	SpawnLoot();
}

void ADCEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADCEnemy::SpawnLoot()
{
	TArray<TSubclassOf<ADCItem>> lootArray;
	Items.GenerateKeyArray(lootArray);
	int32 NumItems = lootArray.Num();
	for (int32 i = 0; i < NumItems; i++)
	{
		if ((FMath::RandRange(0, 100)) <= Items[lootArray[i]])
		{
			SpawnedLoot.Add(lootArray[i]);
		}
	}
}

void ADCEnemy::OnDeath()
{
	if (LootBag)
	{
		UWorld* World = GetWorld();
		FVector Location = GetActorLocation();
		if (World)
		{
			FHitResult Hit;
			FVector Start = GetActorLocation();
			FVector End = Start;
			End.Z -= GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight() * 2;

			if (World->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_Visibility))
			{
				Location = Hit.Location;
			}
		}

		ADCLoot* LootSpawn = GetWorld()->SpawnActor<ADCLoot>(LootBag, Location, GetActorRotation());

		if (LootSpawn)
		{
			LootSpawn->LootContents = SpawnedLoot;
		}
	}

	// destroy enemy and animations
	Destroy();
}

void ADCEnemy::EnemyTakeDamage(int32 Damage)
{
	Health -= Damage;
	UE_LOG(LogTemp, Warning, TEXT("%s Health: %d"), *Name, Health);

	if (Health <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is Dead"), *Name);
		OnDeath();
	}
}