// Fill out your copyright notice in the Description page of Project Settings.

#include "DC.h"
#include "DCEquippable.h"
#include "DCPlayerController.h"
#include "DCCharacter.h"


ADCEquippable::ADCEquippable() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/* Add Mesh to Equippable object. */
	EquippableMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Equippable Mesh"));
	EquippableMesh->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::OnlyTickPoseWhenRendered;
	EquippableMesh->CastShadow = true;
	EquippableMesh->SetupAttachment(RootComponent);

	/* Add Particle slot to Equippable object. */
	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle Effects"));
	ParticleSystem->SetupAttachment(EquippableMesh);

	EquipSocket = "";
}

void ADCEquippable::OnUnEquip() {
	DetachFromPlayer();
}

void ADCEquippable::OnEquip() {
	AttachToPlayer();
}

void ADCEquippable::AttachToPlayer() {
	if (MyOwner) {
		DetachFromPlayer();

		USkeletalMeshComponent* Character = Cast<ADCCharacter>(MyOwner->GetPawn())->GetMesh();
		EquippableMesh->SetHiddenInGame(false);
		ParticleSystem->SetHiddenInGame(false);
		EquippableMesh->AttachToComponent(Character, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, true), EquipSocket);
	}
}

void ADCEquippable::DetachFromPlayer() {
	FDetachmentTransformRules rules(EDetachmentRule::KeepWorld, true);
	EquippableMesh->DetachFromComponent(rules);
	EquippableMesh->SetHiddenInGame(true);
	ParticleSystem->SetHiddenInGame(true);
}

ESlotType ADCEquippable::GetSlotType() {
	return SlotType;
}

USkeletalMeshComponent* ADCEquippable::GetEquippableMesh() {
	return EquippableMesh;
}

UParticleSystemComponent* ADCEquippable::GetParticleSystem() {
	return ParticleSystem;
}
