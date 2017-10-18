// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Particles/ParticleSystemComponent.h"
#include "DCWeatherComponent.generated.h"

UENUM(BlueprintType)
enum class EWeatherType : uint8
{
	Sunny			UMETA(DisplayName = "Sunny"),
	Rainy			UMETA(DisplayName = "Rainy"),
	Cloudy			UMETA(DisplayName = "Cloudy"),
	Stormy			UMETA(DisplayName = "Stormy"),
	Snowy			UMETA(DisplayName = "Snowy"),
	Hot				UMETA(DisplayName = "Hot"),
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DC_API UDCWeatherComponent : public UParticleSystemComponent
{
	GENERATED_BODY()

public:	
	UDCWeatherComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void SetWeather(EWeatherType Type);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	EWeatherType CurrentWeather;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Particles)
	class UParticleSystem* RainyParticles;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Particles)
	class UParticleSystem* SnowyParticles;

};
