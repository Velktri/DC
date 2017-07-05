// Fill out your copyright notice in the Description page of Project Settings.

#include "DC.h"
#include "UI_Render.h"
#include "DCCharacter.h"
#include "DCEquippable.h"
#include "DCPlayerController.h"
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

	/* Generate Current Equipment */
	RenderEquipment.Add(ESlotType::Head,			CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Head")));
	RenderEquipment.Add(ESlotType::Shoulder,		CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Shoulder")));
	RenderEquipment.Add(ESlotType::Chest,			CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Chest")));
	RenderEquipment.Add(ESlotType::Legs,			CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Legs")));
	RenderEquipment.Add(ESlotType::Boots,			CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Boots")));
	RenderEquipment.Add(ESlotType::RightWeapon,		CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightWeapon")));
	RenderEquipment.Add(ESlotType::LeftWeapon,		CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LeftWeapon")));
	RenderEquipment.Add(ESlotType::RangedWeapon,	CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RangedWeapon")));

	for (auto& Elem : RenderEquipment) {
		Elem.Value->SetupAttachment(MeshRoot);
	}
}

void AUI_Render::BeginPlay()
{
	Super::BeginPlay();
	CaptureComponent->SetTickableWhenPaused(true);
	RenderMesh->SetTickableWhenPaused(true);
}

void AUI_Render::SetNewRenderMesh(AActor* InActor, ECaptureStates InputState) {
	GetRenderElements(InActor);
	SetRenderElements();
	MoveCaptureCamera(InputState);

	if (InputState != ECaptureStates::Equipment)
	{
		RenderMesh->SetRelativeLocation(FVector(0, 0, 0));
		RenderMesh->SetRelativeRotation(FRotator(0, 0, 0));
		RenderMesh->SetWorldScale3D(FVector(1, 1, 1));
	}
}

void AUI_Render::AppendEquipmentToRender(ADCEquippable* EquipmentPiece) {
	if (RenderMesh)
	{
		switch (EquipmentPiece->SlotType) {
		case ESlotType::Head:
			EquipToSlot(EquipmentPiece, "Helm");
			break;
		case ESlotType::RightWeapon:
			EquipToSlot(EquipmentPiece, "MainHand");
			break;
		case ESlotType::LeftWeapon:
			EquipToSlot(EquipmentPiece, "OffHand");
			break;
		default:
			break;
		}
	}
}

void AUI_Render::GetRenderElements(AActor* InActor) {
	if (InActor)
	{
		if (InActor->IsA(ADCCharacter::StaticClass())) 
		{
			for (auto& Elem : RenderEquipment) {
				Elem.Value->SetHiddenInGame(false);
			}

			ADCCharacter* Char = Cast<ADCCharacter>(InActor);
			InMesh = Char->GetMesh()->SkeletalMesh;
			InAnimation = Char->GetUIAnimation();
		} 
		else if (InActor->IsA(ADCItem::StaticClass())) 
		{
			for (auto& Elem : RenderEquipment) {
				Elem.Value->SetHiddenInGame(true);
			}

			ADCEquippable* Equippable = Cast<ADCEquippable>(InActor);
			InMesh = Equippable->EquippableMesh->SkeletalMesh;
			InAnimation = Equippable->UI_Animation;
		}
	} 
	else 
	{
		RenderMesh->SetSkeletalMesh(NULL, true);
		InMesh = NULL;
		InAnimation = NULL;
	}
}

void AUI_Render::SetRenderElements() {
	if (RenderMesh)
	{
		if (InMesh) 
		{
			RenderMesh->SetSkeletalMesh(InMesh, true);

			//EquipToSlot(OwningPC->CurrentEquipment[ESlotType::Head],				"Helm");
			////EquipToSlot(OwningPC->CurrentEquipment[ESlotType::Shoulder],			"Helm");	
			////EquipToSlot(OwningPC->CurrentEquipment[ESlotType::Chest],				"Helm");	
			////EquipToSlot(OwningPC->CurrentEquipment[ESlotType::Legs],				"Helm");	
			////EquipToSlot(OwningPC->CurrentEquipment[ESlotType::Boots],				"Helm");
			//EquipToSlot(OwningPC->CurrentEquipment[ESlotType::RightWeapon],			"MainHand");
			//EquipToSlot(OwningPC->CurrentEquipment[ESlotType::LeftWeapon],			"OffHand");
			////EquipToSlot(OwningPC->CurrentEquipment[ESlotType::RangedWeapon],		"Helm");
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

void AUI_Render::EquipToSlot(ADCEquippable* InItem, FName SocketName) {
	if (RenderMesh && InItem) {
		RenderEquipment[InItem->SlotType]->SetSkeletalMesh(InItem->EquippableMesh->SkeletalMesh, true);
		RenderEquipment[InItem->SlotType]->SetWorldScale3D(InItem->EquippableMesh->GetComponentScale());
		RenderEquipment[InItem->SlotType]->AttachToComponent(RenderMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, true), SocketName);
	}
}

