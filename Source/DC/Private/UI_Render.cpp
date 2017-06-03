// Fill out your copyright notice in the Description page of Project Settings.

#include "DC.h"
#include "UI_Render.h"
#include "DCCharacter.h"
#include "DCWeapon.h"
#include "Components/SceneCaptureComponent2D.h"


// Sets default values
AUI_Render::AUI_Render()
{
	PrimaryActorTick.bCanEverTick = false;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Default Scene Root"));
	DefaultSceneRoot->SetupAttachment(RootComponent);

	CaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Capture Component"));
	CaptureComponent->SetupAttachment(DefaultSceneRoot);
	CaptureComponent->FOVAngle = 60.0f;

	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Point Light"));
	PointLight->SetupAttachment(DefaultSceneRoot);

	MeshRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Mesh Root"));
	MeshRoot->SetupAttachment(DefaultSceneRoot);

	RenderMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Render Mesh"));
	RenderMesh->SetupAttachment(MeshRoot);
}

// Called when the game starts or when spawned
void AUI_Render::BeginPlay()
{
	Super::BeginPlay();
	CaptureComponent->SetTickableWhenPaused(true);
	RenderMesh->SetTickableWhenPaused(true);
}

void AUI_Render::SetNewRenderMesh(AActor* InActor, ECaptureStates InputState) {
	GetRenderElements(InActor);
	SetRenderElements(InputState);
	MoveCaptureCamera(InputState);

	if (InputState != ECaptureStates::Equipment)
	{
		RenderMesh->SetRelativeLocation(FVector(0, 0, 0));
		RenderMesh->SetRelativeRotation(FRotator(0, 0, 0));
		RenderMesh->SetWorldScale3D(FVector(1, 1, 1));
	}
}

void AUI_Render::GetRenderElements(AActor* InActor) {
	if (InActor)
	{
		if (InActor->IsA(ADCCharacter::StaticClass())) {
			ADCCharacter* Char = Cast<ADCCharacter>(InActor);
			InMesh = Char->GetMesh()->SkeletalMesh;
			InAnimation = Char->GetUIAnimation();
		} else if (InActor->IsA(ADCItem::StaticClass())) {
			ADCWeapon* Weapon = Cast<ADCWeapon>(InActor);
			InMesh = Weapon->SwordMesh->SkeletalMesh;
			InAnimation = Weapon->UI_Animation;
		}
	} else {
		RenderMesh->SetSkeletalMesh(NULL, true);
		InMesh = NULL;
		InAnimation = NULL;
	}
}

void AUI_Render::SetRenderElements(ECaptureStates InputState) {
	if (RenderMesh)
	{
		if (InMesh) 
		{
			RenderMesh->SetSkeletalMesh(InMesh, true);
		} 
		else 
		{
			RenderMesh->SetSkeletalMesh(NULL, true);
			InMesh = NULL;
			InAnimation = NULL;
		}

		if (InAnimation)
		{
			RenderMesh->PlayAnimation(InAnimation, true);
		}
	}

	InMesh = NULL;
	InAnimation = NULL;
}

void AUI_Render::MoveCaptureCamera(ECaptureStates InputState) {
	FTransform trans;

	switch (InputState) {
	case ECaptureStates::InGame:
		CaptureComponent->SetRelativeLocation(InGameCamLoc);
		CaptureComponent->SetRelativeRotation(InGameCamRot);
		break;
	case ECaptureStates::Equipment:
		ItemCamLoc.Y = 1.73205 * RenderMesh->CalcBounds(trans).BoxExtent.Z;
		CaptureComponent->SetRelativeLocation(ItemCamLoc);
		CaptureComponent->SetRelativeRotation(ItemCamRot);
		break;
	case ECaptureStates::Character:
		CaptureComponent->SetRelativeLocation(CharCamLoc);
		CaptureComponent->SetRelativeRotation(CharCamRot);
		break;
	default:
		CaptureComponent->SetRelativeLocationAndRotation(FVector(0, 0, 0), FRotator(0, 0, 0));
		break;
	}
}

