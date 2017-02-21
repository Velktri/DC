// Fill out your copyright notice in the Description page of Project Settings.

#include "DC.h"
#include "DCLoot.h"
#include "DCItem.h"


// Sets default values
ADCLoot::ADCLoot() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	LootMesh = CreateDefaultSubobject<UStaticMeshComponent>("Loot Mesh");
}

ADCItem* ADCLoot::GetLootContents() {
	return LootContents;
}

int32 ADCLoot::GetMoney() {
	return Money;
}

// Called when the game starts or when spawned
void ADCLoot::BeginPlay() {
	Super::BeginPlay();
	
}