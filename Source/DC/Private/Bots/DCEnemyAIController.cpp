// Fill out your copyright notice in the Description page of Project Settings.

#include "DC.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "DCEnemyAIController.h"
#include "DCEnemy.h"
#include "DCCharacter.h"


ADCEnemyAIController::ADCEnemyAIController() {
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoardComp"));
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
}

void ADCEnemyAIController::Possess(APawn* InPawn) {
	Super::Possess(InPawn);

	ADCEnemy* Bot = Cast<ADCEnemy>(InPawn);

	// start behavior
	if (Bot && Bot->BotBehavior) {
		if (Bot->BotBehavior->BlackboardAsset) {
			BlackboardComp->InitializeBlackboard(*Bot->BotBehavior->BlackboardAsset);
		}

		EnemyKeyID = BlackboardComp->GetKeyID("Target");

		BehaviorComp->StartTree(*(Bot->BotBehavior));
	}
}

void ADCEnemyAIController::SetEnemy(class APawn* InPawn) {
	if (BlackboardComp) {
		BlackboardComp->SetValue<UBlackboardKeyType_Object>(EnemyKeyID, InPawn);
		SetFocus(InPawn);
	}
}

void ADCEnemyAIController::FindMainCharacter() {
	APawn* MyBot = GetPawn();
	if (MyBot == NULL) {
		return;
	}

	const FVector MyLoc = MyBot->GetActorLocation();

	ADCCharacter* BestPawn = Cast<ADCCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	ADCEnemy* MyDCBot = Cast<ADCEnemy>(MyBot);
	if (MyDCBot)
	{
		const float DistSq = (BestPawn->GetActorLocation() - MyLoc).SizeSquared();
		if (DistSq <= (MyDCBot->SightDistance * MyDCBot->SightDistance)) {
			if (BestPawn) {
				SetEnemy(BestPawn);
			}
		}
	}
}

ADCCharacter* ADCEnemyAIController::GetEnemy() const {
	if (BlackboardComp) {
		return Cast<ADCCharacter>(BlackboardComp->GetValue<UBlackboardKeyType_Object>(EnemyKeyID));
	}

	return NULL;
}
