// Fill out your copyright notice in the Description page of Project Settings.

#include "DC.h"
#include "DCEnemy.h"
#include "DCWeapon.h"
#include "DCLoot.h"


// Sets default values
ADCEnemy::ADCEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADCEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADCEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ADCEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ADCEnemy::OnDeath() {
	FVector DeathLoc = GetActorLocation();
	DeathLoc.Z -= 90.0f;
	FRotator DeathRot = GetActorRotation();
	ADCLoot* LootSpawn = GetWorld()->SpawnActor<ADCLoot>(LootBag, DeathLoc, DeathRot);

	if (LootSpawn) {
		if (LootReference.Num() > 0 && DropPercentage.Num() > 0) {
			if (LootReference.Num() == DropPercentage.Num()) {
				int32 RandomNumber = FMath::RandRange(1, 100);
				TSubclassOf<class ADCItem> LootChoice = NULL;
				for (int32 i = 0; i < DropPercentage.Num(); i++) {
					if (RandomNumber <= DropPercentage[i]) {
						LootChoice = LootReference[i];
						break;
					}
				}

				ADCItem* Spawner = GetWorld()->SpawnActor<ADCItem>(LootChoice);
				if (Spawner) {
					Item = Spawner;

					if (Item->IsA(ADCWeapon::StaticClass())) {
						Cast<ADCWeapon>(Item)->SwordMesh->SetHiddenInGame(true);
						Cast<ADCWeapon>(Item)->OurParticleSystem->SetHiddenInGame(true);
					}


					LootSpawn->LootContents = Item;
				}
			} else {
				UE_LOG(LogTemp, Warning, TEXT("Loot Reference and Drop Percentage mismatch error."));
				//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "Loot Reference and Drop Percentage mismatch error.");
			}
		}
	}

	// destroy enemy and animations
	this->Destroy();
}

void ADCEnemy::EnemyTakeDamage(int32 Damage) {
	Health -= Damage;
	UE_LOG(LogTemp, Warning, TEXT("%s Health: %d"), *Name, Health);
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, FString::FromInt(Health));

	if (Health <= 0) {
		UE_LOG(LogTemp, Warning, TEXT("%s is Dead"), *Name);
		OnDeath();
	}
}

