// Fill out your copyright notice in the Description page of Project Settings.

#include "DC.h"
#include "DCWeatherComponent.h"

UDCWeatherComponent::UDCWeatherComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	CurrentWeather = EWeatherType::Sunny;
}

void UDCWeatherComponent::BeginPlay()
{
	Super::BeginPlay();
	SetWeather(CurrentWeather);
}

void UDCWeatherComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UDCWeatherComponent::SetWeather(EWeatherType Type)
{
	switch (Type)
	{
	case EWeatherType::Stormy:
		// add lightning system

	case EWeatherType::Rainy:
		SetTemplate(RainyParticles);

	case EWeatherType::Cloudy:
		// set cloudy skybox
		break;
	case EWeatherType::Snowy:
		SetTemplate(SnowyParticles);
		break;
	case EWeatherType::Hot:
		// set overheating template

	case EWeatherType::Sunny:
		SetTemplate(NULL);
		// set sunny skybox
		break;
	default:
		UE_LOG(LogTemp, Error, TEXT("Unknown Weather Type"));
		break;
	}

	SetActive(true);
}

