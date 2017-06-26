// Fill out your copyright notice in the Description page of Project Settings.

#include "DC.h"
#include "UI_Render.h"
#include "DCCharacter.h"
#include "DCEquippable.h"
#include "Components/SceneCaptureComponent2D.h"

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

	Ingame.Position = FVector(20.65, 56.08, 153.79);
	Ingame.Rotation = FRotator(7.64, -112, -1.21);

	Character.Position = FVector(43.14, 245.15, 150.29);
	Character.Rotation = FRotator(-9.84, -99.84, -1.75);

	Item.Position = FVector(7.50, 224.87, 48.94);
	Item.Rotation = FRotator(0, 270, 0);
}

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

void AUI_Render::AppendEquipmentToRender() {

}

void AUI_Render::GetRenderElements(AActor* InActor) {
	if (InActor)
	{
		if (InActor->IsA(ADCCharacter::StaticClass())) {
			ADCCharacter* Char = Cast<ADCCharacter>(InActor);
			InMesh = Char->GetMesh()->SkeletalMesh;
			InAnimation = Char->GetUIAnimation();
		} else if (InActor->IsA(ADCItem::StaticClass())) {
			ADCEquippable* Equippable = Cast<ADCEquippable>(InActor);
			InMesh = Equippable->EquippableMesh->SkeletalMesh;
			InAnimation = Equippable->UI_Animation;
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

		if (InAnimation) { RenderMesh->PlayAnimation(InAnimation, true); }
	}

	InMesh = NULL;
	InAnimation = NULL;
}

void AUI_Render::MoveCaptureCamera(ECaptureStates InputState) {
	FTransform trans;

	switch (InputState) {
	case ECaptureStates::InGame:
		CaptureComponent->SetRelativeLocation(Ingame.Position);
		CaptureComponent->SetRelativeRotation(Ingame.Rotation);
		break;
	case ECaptureStates::Equipment:
		Item.Position.Y = 1.73205 * RenderMesh->CalcBounds(trans).BoxExtent.Z;
		CaptureComponent->SetRelativeLocation(Item.Position);
		CaptureComponent->SetRelativeRotation(Item.Rotation);
		break;
	case ECaptureStates::Character:
		CaptureComponent->SetRelativeLocation(Character.Position);
		CaptureComponent->SetRelativeRotation(Character.Rotation);
		break;
	default:
		CaptureComponent->SetRelativeLocationAndRotation(FVector(0, 0, 0), FRotator(0, 0, 0));
		break;
	}
}

