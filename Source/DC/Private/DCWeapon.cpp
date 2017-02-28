// Fill out your copyright notice in the Description page of Project Settings.

#include "DC.h"
#include "DCWeapon.h"
#include "DCCharacter.h"
#include "DCEnemy.h"

ADCWeapon::ADCWeapon() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/* Add Mesh to weapon object. */
	SwordMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));
	SwordMesh->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::OnlyTickPoseWhenRendered;
	SwordMesh->CastShadow = true;
	SwordMesh->AttachTo(RootComponent);

	/* Add Collision to object. */
	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	CollisionComp->AttachTo(SwordMesh);
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ADCWeapon::OnCollision);

	/* Add Particle slot to weapon object. */
	OurParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle Effects"));
	OurParticleSystem->AttachTo(SwordMesh);
}

UBoxComponent* ADCWeapon::GetCollisionComp() {
	if (CollisionComp) {
		return CollisionComp;
	}

	return NULL;
}

void ADCWeapon::OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) {
	if (OtherActor->IsA(ADCEnemy::StaticClass())) {
		ADCEnemy* Enemy = Cast<ADCEnemy>(OtherActor);
		Enemy->EnemyTakeDamage(10);
		CollisionComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ADCWeapon::OnUnEquip() {
	DetachFromPlayer();
}

void ADCWeapon::OnEquip() {
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AttachToPlayer();
}

void ADCWeapon::AttachToPlayer() {
	if (MyPawn) {
		DetachFromPlayer();

		USkeletalMeshComponent* Character = MyPawn->GetMesh();
		SwordMesh->SetHiddenInGame(false);
		OurParticleSystem->SetHiddenInGame(false);
		SwordMesh->AttachTo(Character, "weapon_r", EAttachLocation::SnapToTarget, true);
		//SwordMesh->AttachTo(Character, "weapon_r");
	}
}

void ADCWeapon::DetachFromPlayer() {
	SwordMesh->DetachFromParent();
	SwordMesh->SetHiddenInGame(true);
	OurParticleSystem->SetHiddenInGame(true);
}
