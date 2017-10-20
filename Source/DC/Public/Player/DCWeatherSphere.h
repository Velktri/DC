// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DCWeatherSphere.generated.h"

USTRUCT(BlueprintType)
struct FDCWorldClock
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Clock)
	int32 Minutes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Clock)
	int32 Hours;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Clock)
	int32 Days;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Clock)
	int32 Months;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Clock)
	int32 Years;

	FDCWorldClock()
	{
		Minutes = 0;
		Hours = 0;
		Days = 0;
		Months = 0;
		Years = 0;
	}

	void AddMinutes(int32 InMinutes)
	{
		Minutes += InMinutes;
		if ((Minutes / 60) > 0) { AddHours((Minutes / 60)); }
		if (Minutes >= 60) { Minutes = Minutes % 60; }
	}

	void AddHours(int32 InHours)
	{
		Hours += InHours;
		if ((Hours / 24) > 0) { AddDays((Hours / 24)); }
		if (Hours >= 24) { Hours = Hours % 24; }
	}

	void AddDays(int32 InDays)
	{
		Days += InDays;
		if ((Days / 30) > 0) { AddMonths((Days / 30)); }
		if (Days >= 30) { Days = Days % 30; }
	}

	void AddMonths(int32 InMonths)
	{
		Months += InMonths;
		if ((Months / 12) > 0) { AddYears((Months / 12)); }
		if (Months >= 12) { Months = Months % 12; }
	}

	void AddYears(int32 InYears)
	{
		Years += InYears;
	}
};

UCLASS()
class DC_API ADCWeatherSphere : public AActor
{
	GENERATED_BODY()
	
public:	
	ADCWeatherSphere();

	UFUNCTION()
	void UpdateSkyMaterial();

	UFUNCTION()
	void SyncSunAngleToClock();

	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION()
	void SetWorldTime();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UStaticMeshComponent* SkyMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UMaterialInstanceDynamic* SkyMaterial;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UDirectionalLightComponent* SunDirectionLight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USkyLightComponent* SkyLight;

	UPROPERTY()
	class UArrowComponent* ArrowComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UCurveLinearColor* CloudColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UCurveLinearColor* HorizonColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UCurveLinearColor* ZenithColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float CloudSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float SunBrightness;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float CloudOpacity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float StarsBrightness;

	/* Day Night Cycle */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DayLengthToMinutes;

	float DayLengthModifier;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Day Cycle")
	FDCWorldClock Clock;

	float ElapsedTime;
	float SunAngle;
	float SunDelta;
	const float AngleTickConstant = 1.0f / 240.0f;

};
