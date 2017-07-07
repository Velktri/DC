// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DCLoot.generated.h"

UCLASS()
class DC_API ADCLoot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADCLoot();

	/** The loot inside the loot bag */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config | Loot")
	TArray<TSubclassOf<class ADCItem>> LootContents;

	/*  GETTERS  */
	TArray<TSubclassOf<class ADCItem>> GetLootContents();
	int32 GetMoney();

protected:

	/** Amount of money inside loot bag */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Config | Loot")
	int32 Money;

	/** Loot Mesh */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Config | Loot")
	UStaticMeshComponent* LootMesh;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
