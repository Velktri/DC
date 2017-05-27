// Fill out your copyright notice in the Description page of Project Settings.

#include "DC.h"
#include "DCItem.h"
#include "DCCharacter.h"


// Sets default values
ADCItem::ADCItem() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

FString ADCItem::GetItemName() {
	return ItemName;
}

// Called when the game starts or when spawned
void ADCItem::BeginPlay()
{
	Super::BeginPlay();
}

void ADCItem::SetOwner(ADCPlayerController* NewOwner) {
	if (MyOwner != NewOwner) {
		//Instigator = NewOwner;
		MyOwner = NewOwner;
	}
}