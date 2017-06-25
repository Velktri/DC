// Fill out your copyright notice in the Description page of Project Settings.

#include "DC.h"
#include "DCMeleeWeapon.h"
#include "DCEnemy.h"


ADCMeleeWeapon::ADCMeleeWeapon() {

	/* Add Collision to object. */
	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	CollisionComp->SetupAttachment(EquippableMesh);
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ADCMeleeWeapon::OnCollision);
}

void ADCMeleeWeapon::OnEquip() {
	Super::OnEquip();
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UBoxComponent* ADCMeleeWeapon::GetCollisionComp() {
	return (CollisionComp) ? CollisionComp : NULL;
}

void ADCMeleeWeapon::OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) {
	if (OtherActor->IsA(ADCEnemy::StaticClass())) {
		ADCEnemy* Enemy = Cast<ADCEnemy>(OtherActor);
		Enemy->EnemyTakeDamage(10);
		CollisionComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}