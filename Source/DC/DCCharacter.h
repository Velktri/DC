// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "DCCharacter.generated.h"

#define LOCKON_RADIUS 1000.0f

UENUM(BlueprintType)
enum class ECharState : uint8 {
	I		UMETA(DisplayName = "Idle"),
	A		UMETA(DisplayName = "Attacking"),
	B		UMETA(DisplayName = "Blocking"),
	C		UMETA(DisplayName = "Countering"),
	E		UMETA(DisplayName = "Equipping"),
};

UCLASS(config=Game)
class ADCCharacter : public ACharacter {
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	ADCCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Update the character. (Running, health etc). */
	virtual void Tick(float DeltaSeconds) override;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Current Weapon the character is holding. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	class ADCWeapon* CurrentWeapon;

	/** Inventory for the Character. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory)
	TArray<class ADCItem*> Inventory;

	/** Current health of the Pawn. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	int32 Health;

	/** Max Inventory size for the Character */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inventory)
	int32 MaxInventorySize;

	/** Determine what is in the lootbag. */
	UFUNCTION()
	ADCItem* ProcessLoot(AActor* OtherActor);

	UFUNCTION()
	void EquipNextWeapon();

	UFUNCTION()
	void EquipWeapon(int32 SlotPointer);

	/** Print the current inventory */
	void PrintInventory();

	void Attack();

	void EndAttack();

	/** Locks the camera to an enemy close to the Player. */
	UFUNCTION()
	void LockOn();

	bool bIsLockedOn;

	/** Target that is currently locked on. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Config)
	class ADCEnemy* LockOnTarget;

	/** State of the character. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Config)
	ECharState ActionState;

	/** Collision for Character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision)
	UBoxComponent* CollisionComp;


protected:

	UFUNCTION()
	void OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);


	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	/** Animation for a horizontal slash attack. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* HorzontalSlash;

	/* Pointer to the equipped item slot */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory)
	int32 EquippedItemSlot;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

