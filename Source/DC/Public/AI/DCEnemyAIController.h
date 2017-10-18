// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "DCEnemyAIController.generated.h"

class UBehaviorTreeComponent;
class UBlackboardComponent;

/**
 * 
 */
UCLASS()
class DC_API ADCEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	ADCEnemyAIController();
	
private:
	UPROPERTY(transient)
	UBlackboardComponent* BlackboardComp;

	/* Cached BT component */
	UPROPERTY(transient)
	UBehaviorTreeComponent* BehaviorComp;
	

protected:
	int32 EnemyKeyID;

public:
	virtual void Possess(class APawn* InPawn) override;

	UFUNCTION(BlueprintCallable, Category = Behavior)
	void SetEnemy(class APawn* InPawn);

	/* Finds the closest enemy and sets them as current target */
	UFUNCTION(BlueprintCallable, Category = Behavior)
	void FindMainCharacter();

	class ADCCharacter* GetEnemy() const;


	/** Returns BlackboardComp subobject **/
	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }
	/** Returns BehaviorComp subobject **/
	FORCEINLINE UBehaviorTreeComponent* GetBehaviorComp() const { return BehaviorComp; }
};
