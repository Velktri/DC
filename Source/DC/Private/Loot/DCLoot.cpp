// Fill out your copyright notice in the Description page of Project Settings.

#include "DC.h"
#include "DCLoot.h"
#include "DCItem.h"

ADCLoot::ADCLoot()
{
	PrimaryActorTick.bCanEverTick = false;
	LootMesh = CreateDefaultSubobject<UStaticMeshComponent>("Loot Mesh");
}

TArray<TSubclassOf<class ADCItem>> ADCLoot::GetLootContents()
{
	return LootContents;
}

int32 ADCLoot::GetMoney()
{
	return Money;
}