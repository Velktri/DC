// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "DC.h"
#include "Kismet/HeadMountedDisplayFunctionLibrary.h"
#include "DCCharacter.h"
#include "DCMeleeWeapon.h"
#include "DCLoot.h"
#include "DCItem.h"
#include "DCEnemy.h"
#include "EngineUtils.h"
#include "DCPlayerController.h"
#include "DCGameUIWidget.h"

ADCCharacter::ADCCharacter() {

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ADCCharacter::OnCollision);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

void ADCCharacter::BeginPlay()
{
	Super::BeginPlay();
	ActionState = ECharState::I;

	CurrentHealth = StartingHealth;
	CurrentEnergy = StartingEnergy;
}

void ADCCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bIsLockedOn) {
		float EnemyDistance = FVector::Dist(GetActorLocation(), LockOnTarget->GetActorLocation());
		if (LockOnTarget == NULL || LockOnTarget->IsPendingKill() || (EnemyDistance > (LOCKON_RADIUS * 1.2))) {
			bIsLockedOn = false;
		} else {
			// aim Character at current enemy
			FVector EnemyLocation = LockOnTarget->GetActorLocation();
			FVector MyLocation = GetActorLocation();
			EnemyLocation.Z = 0;
			MyLocation.Z = 0;
			FRotator Rot = FRotationMatrix::MakeFromX(EnemyLocation - MyLocation).Rotator();
			SetActorRotation(Rot);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void ADCCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) {
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ADCCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADCCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ADCCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ADCCharacter::LookUpAtRate);

	/** Equippable swapping */
	//InputComponent->BindAction("NextEquippable", IE_Pressed, this, &ADCCharacter::EquipNextEquippable);

	/** Lock on to targets */
	InputComponent->BindAction("LockOn", IE_Pressed, this, &ADCCharacter::LockOn);

	/** Equippable Attacks */
	InputComponent->BindAction("Attack", IE_Pressed, this, &ADCCharacter::Attack);
}

void ADCCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ADCCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ADCCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ADCCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}


void ADCCharacter::ProcessLoot(TArray<TSubclassOf<ADCItem>> lootItems)
{
	for (TSubclassOf<ADCItem> loot : lootItems)
	{
		if (loot)
		{
			ADCItem* Spawner = GetWorld()->SpawnActor<ADCItem>(loot);
			if (Spawner && Spawner->IsA(ADCEquippable::StaticClass()))
			{
				Cast<ADCEquippable>(Spawner)->GetEquippableMesh()->SetHiddenInGame(true);
				Cast<ADCEquippable>(Spawner)->GetParticleSystem()->SetHiddenInGame(true);

				AController* PC = GetController();
				if (PC)
				{
					Cast<ADCPlayerController>(PC)->AddToInventory(Spawner);
				}
			}
		}
	}
}

void ADCCharacter::Attack() {
	if (GetController() && GetController()->IsA(ADCPlayerController::StaticClass())) {
		ADCMeleeWeapon* CurrentWeapon = Cast<ADCMeleeWeapon>(Cast<ADCPlayerController>(GetController())->GetCurrentEquipment()[ESlotType::RightWeapon]);
		if (CurrentWeapon != NULL && ActionState == ECharState::I) {
			ActionState = ECharState::A;

			UBoxComponent* EquippableCollision = CurrentWeapon->GetCollisionComp();
			if (EquippableCollision) {
				CurrentWeapon->GetCollisionComp()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			}
			EndAttack();
			//float AttackDuration = 0.0f;
			//if (HorzontalSlash) {
			//	AttackDuration = PlayAnimMontage(HorzontalSlash);
			//}

			//if (AttackDuration > 0.f) {
			//	FTimerHandle TimerHandle;
			//	GetWorldTimerManager().SetTimer(TimerHandle, this, &ADCCharacter::EndAttack, AttackDuration, false);
			//}
		}
	}
}

void ADCCharacter::EndAttack() {
	if (GetController() && GetController()->IsA(ADCPlayerController::StaticClass())) {
		ActionState = ECharState::I;
		Cast<ADCMeleeWeapon>(Cast<ADCPlayerController>(GetController())->GetCurrentEquipment()[ESlotType::RightWeapon])->GetCollisionComp()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ADCCharacter::LockOn() {
	if (bIsLockedOn) {
		bIsLockedOn = false;
		LockOnTarget = NULL;
	} else {
		float ClosestDistance = LOCKON_RADIUS;
		for (TActorIterator<ADCEnemy> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
			ADCEnemy* Enemy = *ActorItr;
			float EnemyDistance = FVector::Dist(GetActorLocation(), Enemy->GetActorLocation());

			if (EnemyDistance < LOCKON_RADIUS) {
				if (EnemyDistance < ClosestDistance) {
					ClosestDistance = EnemyDistance;
					LockOnTarget = Enemy;
				}
			}
		}

		// in future, prioritize best target
		// currently will get the closest one
		if (LockOnTarget != NULL) {
			bIsLockedOn = true;
			UE_LOG(LogTemp, Warning, TEXT("%s"), *LockOnTarget->GetName());
		}
	}
}

UAnimationAsset* ADCCharacter::GetUIAnimation() {
	return UI_Animation;
}

void ADCCharacter::OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) {
	if (OtherActor->IsA(ADCLoot::StaticClass())) {

		ProcessLoot(Cast<ADCLoot>(OtherActor)->GetLootContents());

		OtherActor->Destroy();
	}
}
