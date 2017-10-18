// Fill out your copyright notice in the Description page of Project Settings.

#include "DC.h"
#include "DCChest.h"
#include "DCCharacter.h"

ADCChest::ADCChest()
{
	PrimaryActorTick.bCanEverTick = false;

	OpeningTrigger = CreateDefaultSubobject<UBoxComponent>("Trigger Box");
	OpeningTrigger->SetCollisionObjectType(ECC_WorldDynamic);
	OpeningTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OpeningTrigger->OnComponentBeginOverlap.AddDynamic(this, &ADCChest::EnterCollision);
	OpeningTrigger->OnComponentEndOverlap.AddDynamic(this, &ADCChest::LeaveCollision);
	RootComponent = OpeningTrigger;

	ChestMesh = CreateDefaultSubobject<UStaticMeshComponent>("Chest Mesh");
	ChestMesh->SetupAttachment(RootComponent);

	bIsLocked = false;
}

TArray<TSubclassOf<class ADCItem>> ADCChest::GetLootContents()
{
	return ChestItems;
}

UBoxComponent* ADCChest::GetTrigger()
{
	return OpeningTrigger;
}

void ADCChest::LootChest()
{
	ChestItems.Empty();
	// run chest opening animation

	if (ChestItems.Num() == 0)
	{
		OpeningTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ADCChest::EnterCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (!bIsLocked)
	{
		if (OtherActor->IsA(ADCCharacter::StaticClass()))
		{
			Cast<ADCCharacter>(OtherActor)->FocusedChest = this;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is Locked!"), *GetName());
	}
}

void ADCChest::LeaveCollision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(ADCCharacter::StaticClass()))
	{
		ADCCharacter* Char = Cast<ADCCharacter>(OtherActor);
		if (Char->FocusedChest == this)
		{
			Char->FocusedChest = NULL;
		}
	}
}
