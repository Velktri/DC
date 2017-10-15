// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "DCTypes.h"
#include "DCCharacter.generated.h"

#define LOCKON_RADIUS 1000.0f


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

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Max health of the Pawn. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Stats)
	int32 Health;

	/** Init health of the Pawn. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Stats)
	int32 StartingHealth;

	/** Current health of the Pawn. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
	int32 CurrentHealth;

	/** Max Energy of the Pawn. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Stats)
	int32 Energy;

	/** Init Energy of the Pawn. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Stats)
	int32 StartingEnergy;

	/** Current Energy of the Pawn. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stats)
	int32 CurrentEnergy;

	/** Determine what is in the lootbag. */
	UFUNCTION()
	void ProcessLoot(TArray<TSubclassOf<ADCItem>> lootItems);

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

	UFUNCTION()
	UAnimationAsset* GetUIAnimation();

protected:

	UFUNCTION()
	void OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

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

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	/** Animation for a horizontal slash attack. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config | Animation")
	UAnimMontage* HorzontalSlash;

	/** Pawn Defensive Animation. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config | Animation")
	UAnimMontage* DefensiveAnimation;

	/** Animation to play in the Start Menu. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config | Animation")
	UAnimationAsset* UI_Animation;

	/* Pointer to the equipped item slot */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory)
	int32 EquippedItemSlot;

	/*********************** IK Foot/Hands **************************/
	virtual void OnConstruction(const FTransform& Transform) override;

	float Scale;
	float IKTraceDistance;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = IK)
	float IKOffsetRightFoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = IK)
	float IKOffsetLeftFoot;

protected:
	float IKInterpSpeed;

	static FName RightFootIKSocket;
	static FName LeftFootIKSocket;

	float IKFootTrace(float TraceDistance, FName Socket);


	/****************************************************************/

public:
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

