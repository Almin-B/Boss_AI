// Fill out your copyright notice in the Description page of Project Settings.


#include "ObservBlockedHits.h"

UObservBlockedHits::UObservBlockedHits()
{
	NodeName = TEXT("ObservBlockedHits");
}

void UObservBlockedHits::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* AIOwner = OwnerComp.GetAIOwner();
	APawn* OwnerPawn = AIOwner->GetPawn();

	AEnemy_Base* Enemy = Cast<AEnemy_Base>(OwnerPawn);

	if (Enemy)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsInt(BlockedHits.SelectedKeyName, Enemy->BlockedHits);
	}

}
