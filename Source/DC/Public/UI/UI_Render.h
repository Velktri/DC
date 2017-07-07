// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DCTypes.h"
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

USTRUCT()
struct FCameraVectors {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Position")
	FVector Position;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
	FRotator Rotation;
};

UCLASS()
class DC_API AUI_Render : public AActor
{
	GENERATED_BODY()
	
public:	
	AUI_Render();

	/** Called by outside functions to update Render Target */
	UFUNCTION(BlueprintCallable)
	void SetNewRenderMesh(class AActor* InActor, ECaptureStates InputState);


	/** Add equipment to Mesh */
	UFUNCTION(Category = "Config")
	void AppendEquipmentToRender(ADCEquippable* EquipmentPiece);

	/** Owning Player Controller */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Config | Inventory")
	class ADCPlayerController* OwningPC;

	/* GETTERS */
	UFUNCTION()
	USkeletalMeshComponent* GetRenderMesh();

protected:
	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

	/** Capture Component */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config | Components")
	USceneComponent* DefaultSceneRoot;

	/** Capture Component */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config | Components")
	class USceneCaptureComponent2D* CaptureComponent;

	/** Lighting */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config | Components")
	UPointLightComponent* PointLight;

	/** Mesh Root */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config | Components")
	USceneComponent* MeshRoot;

	/** Render Mesh */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config | Components")
	USkeletalMeshComponent* RenderMesh;

	/** Current Equipment the character is holding. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Config | Inventory")
	TMap<ESlotType, USkeletalMeshComponent*> RenderEquipment;

private:
	USkeletalMesh* InMesh;
	UAnimationAsset* InAnimation;

	FCameraVectors Ingame;
	FCameraVectors Character;
	FCameraVectors Item;

	/** Extract the render elements from the actor */
	void GetRenderElements(class AActor* InActor);

	/** Apply extracted elements to the render target */
	void SetRenderElements();

	void MoveCaptureCamera(ECaptureStates InputState);

	/** Attach Render Equipment to Render Mesh */
	void EquipToSlot(ADCEquippable* InItem, FName SocketName);
};
