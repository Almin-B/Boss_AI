// Fill out your copyright notice in the Description page of Project Settings.


#include "ResetBlockedHitsCounter.h"

UResetBlockedHitsCounter::UResetBlockedHitsCounter(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("ResetBlockedHitsCounter");
}

EBTNodeResult::Type UResetBlockedHitsCounter::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIOwner = OwnerComp.GetAIOwner();
	APawn* OwnerPawn = AIOwner->GetPawn();

	AEnemy_Base* Enemy = Cast<AEnemy_Base>(OwnerPawn);

	if (Enemy)
	{
		Enemy->BlockedHits = 0;
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;


}
