// Fill out your copyright notice in the Description page of Project Settings.

#include "DC.h"
#include "DCWeatherSphere.h"
#include "Components/StaticMeshComponent.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/SkyLightComponent.h"
#include "Components/ArrowComponent.h"
#include "Curves/CurveLinearColor.h"
#include "Engine/Engine.h"

ADCWeatherSphere::ADCWeatherSphere()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Origin"));

	SkyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sky Mesh"));
	SkyMesh->SetupAttachment(RootComponent);
	SkyMesh->bCastDynamicShadow = false;
	SkyMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SkyMesh->SetWorldScale3D(FVector(400, 400, 400));

	SunDirectionLight = CreateDefaultSubobject<UDirectionalLightComponent>(TEXT("Sun Light"));
	SunDirectionLight->SetupAttachment(RootComponent);
	SunDirectionLight->Intensity = 2.75;
	SunDirectionLight->Mobility = EComponentMobility::Movable;
	SunDirectionLight->bUsedAsAtmosphereSunLight = true;
	SunDirectionLight->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 750.0f), FRotator(90.0f, 0.0f, 0.0f));

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	ArrowComponent->SetupAttachment(SunDirectionLight);
	ArrowComponent->ArrowColor = FColor::Emerald;

	SkyLight = CreateDefaultSubobject<USkyLightComponent>(TEXT("Sky Light"));
	SkyLight->SetupAttachment(RootComponent);
	SkyLight->SetRelativeLocation(FVector(0, 0, 600));

	SunBrightness = 50.0f;
	CloudSpeed = 1.0f;
	CloudOpacity = 0.7f;
	StarsBrightness = 0.1f;

	DayLengthToMinutes = 2.0f;
	SunDelta = 0.0f;
}

void ADCWeatherSphere::UpdateSkyMaterial()
{
	if (SunDirectionLight && SkyMaterial)
	{
		FVector SunDirection = SunDirectionLight->GetRelativeTransform().Rotator().Vector();
		SkyMaterial->SetVectorParameterValue(FName("Light direction"), SunDirection);

		FColor SunColor = SunDirectionLight->LightColor;
		SkyMaterial->SetVectorParameterValue(FName("Sun color"), SunColor);

		float SunHeight = FMath::GetMappedRangeValueUnclamped(FVector2D(0.0f, -90.0f), FVector2D(0.0f, 1.0f), SunDirectionLight->GetRelativeTransform().Rotator().Pitch);

		if (HorizonColor) { SkyMaterial->SetVectorParameterValue(FName("Horizon color"), HorizonColor->GetLinearColorValue(SunHeight)); }
		if (ZenithColor) { SkyMaterial->SetVectorParameterValue(FName("Zenith color"), ZenithColor->GetLinearColorValue(SunHeight)); }
		if (CloudColor) { SkyMaterial->SetVectorParameterValue(FName("Cloud color"), CloudColor->GetLinearColorValue(SunHeight)); }

		float falloff = 3 + FMath::Abs(SunHeight) * (7 - 3);
		SkyMaterial->SetScalarParameterValue(FName("Horizon falloff"), falloff);

		SkyMaterial->SetScalarParameterValue(FName("Cloud speed"), CloudSpeed);
		SkyMaterial->SetScalarParameterValue(FName("Sun brightness"), SunBrightness);

		float height = (SunHeight < 0) ? FMath::Abs(SunHeight) : 0.0f;
		SkyMaterial->SetScalarParameterValue(FName("Sun height"), height);
		SkyMaterial->SetScalarParameterValue(FName("Cloud opacity"), CloudOpacity);
		SkyMaterial->SetScalarParameterValue(FName("Stars brightness"), StarsBrightness);
	}
}

void ADCWeatherSphere::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	float Angle = AngleTickConstant * DeltaSeconds * DayLengthModifier;
	GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Green, FString::Printf(TEXT("Angle: %f"), Angle));

	SunDirectionLight->AddLocalRotation(FRotator(-1 * Angle, 0.0f, 0.0f));
	ElapsedTime += DeltaSeconds;
	GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::Printf(TEXT("Elapsed Time: %f"), ElapsedTime));

	SunDelta += Angle;
	if (SunDelta >= 0.25)
	{
		int32 mins = SunDelta / 0.25;
		Clock.AddMinutes(mins);
		SunDelta -= 0.25 * mins;
	}

	GEngine->AddOnScreenDebugMessage(2, 5.f, FColor::Blue, FString::Printf(TEXT("Years: %d\nMonth: %d\nDay: %d\nClock: %d:%d"), Clock.Years, Clock.Months, Clock.Days, Clock.Hours, Clock.Minutes));
	UpdateSkyMaterial();
}

void ADCWeatherSphere::BeginPlay()
{
	Super::BeginPlay();
	SetWorldTime();
	SyncSunAngleToClock();
	DayLengthModifier = 1440 / DayLengthToMinutes;
}

void ADCWeatherSphere::OnConstruction(const FTransform& Transform)
{
	UMaterialInterface* Mat = SkyMesh->GetMaterial(0);
	if (Mat)
	{
		SkyMaterial = SkyMesh->CreateDynamicMaterialInstance(0, Mat);
		UpdateSkyMaterial();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Static Mesh %s has no material."), *SkyMesh->GetName());
	}
}

void ADCWeatherSphere::SetWorldTime()
{
	Clock = FDCWorldClock();
}

void ADCWeatherSphere::SyncSunAngleToClock()
{
	SunAngle = (((60 * Clock.Hours) + Clock.Minutes) / 1440.0f) + 90;
	SunDirectionLight->SetWorldRotation(FRotator(SunAngle, 0.0f, 0.0f));
	UpdateSkyMaterial();
}
