// Fill out your copyright notice in the Description page of Project Settings.


#include "GetDistanceTarget.h"

UGetDistanceTarget::UGetDistanceTarget()
{
	NodeName = TEXT("GetDistanceToTarget");
}

void UGetDistanceTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* AIOwner = OwnerComp.GetAIOwner();
	APawn* OwnerPawn = AIOwner->GetPawn();

	if (OwnerPawn)
	{
		float DistanceToTarget = (OwnerPawn->GetActorLocation() - OwnerComp.GetBlackboardComponent()->GetValueAsVector(TargetLocation.SelectedKeyName)).Size();
		OwnerComp.GetBlackboardComponent()->SetValueAsFloat(Distance.SelectedKeyName, DistanceToTarget);
	}
}
