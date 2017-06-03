// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UI_Render.generated.h"

class USkeletalMesh;
class UAnimationAsset;

UENUM(BlueprintType)
enum class ECaptureStates : uint8 {
	InGame			UMETA(DisplayName = "InGame"),
	Equipment		UMETA(DisplayName = "Equipment"),
	Character		UMETA(DisplayName = "Character"),
	None			UMETA(DisplayName = "None"),
};

UCLASS()
class DC_API AUI_Render : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUI_Render();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	/** Called by outside functions to update Render Target */
	UFUNCTION(BlueprintCallable)
	void SetNewRenderMesh(class AActor* InActor, ECaptureStates InputState);

	/** Capture Component */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	USceneComponent* DefaultSceneRoot;

	/** Capture Component */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	class USceneCaptureComponent2D* CaptureComponent;

	/** Lighting */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	UPointLightComponent* PointLight;

	/** Mesh Root */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	USceneComponent* MeshRoot;

	/** Render Mesh */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	USkeletalMeshComponent* RenderMesh;

private:
	USkeletalMesh* InMesh;
	UAnimationAsset* InAnimation;

	FVector InGameCamLoc = FVector(20.65, 56.08, 153.79);
	FRotator InGameCamRot = FRotator(7.64, -112, -1.21); //    Y, Z, X

	FVector CharCamLoc = FVector(43.14, 245.15, 150.29);
	FRotator CharCamRot = FRotator(-9.84, -99.84, -1.75); //   Y, Z, X

	FVector ItemCamLoc = FVector(7.50, 224.87, 48.94);
	FRotator ItemCamRot = FRotator(0, 270, 0); //    Y, Z, X

	/** Extract the render elements from the actor */
	void GetRenderElements(class AActor* InActor);

	/** Apply extracted elements to the render target */
	void SetRenderElements(ECaptureStates InputState);

	void MoveCaptureCamera(ECaptureStates InputState);
};
