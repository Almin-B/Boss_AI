// Fill out your copyright notice in the Description page of Project Settings.


#include "GetDistanceToTarget.h"

UGetDistanceToTarget::UGetDistanceToTarget(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("GetDistanceToTarget");
}

EBTNodeResult::Type UGetDistanceToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIOwner = OwnerComp.GetAIOwner();
	APawn* OwnerPawn = AIOwner->GetPawn();

	FVector TargetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(FName("TargetLocation"));
	FVector EnemyLocation = OwnerPawn->GetActorLocation();

	float TargetDistance;

	TargetDistance = (TargetLocation - EnemyLocation).Size();

	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(GetSelectedBlackboardKey(),TargetDistance);

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
