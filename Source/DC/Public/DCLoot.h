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

	/** Loot Mesh */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Config)
	UStaticMeshComponent* LootMesh;

	/** The loot inside the loogbag */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Loot)
	class ADCItem* LootContents;

	/** Amount of money inside loot bag */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Loot)
	int32 Money;

	/** Returns the name of the loot contents */
	UFUNCTION()
	ADCItem* GetLootContents();

	/** Returns the amount of money in the loot */
	UFUNCTION()
	int32 GetMoney();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
