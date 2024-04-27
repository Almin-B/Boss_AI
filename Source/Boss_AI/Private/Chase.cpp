// Fill out your copyright notice in the Description page of Project Settings.


#include "Chase.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Math/Vector.h"

UChase::UChase(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("ChaseTarget");

}

EBTNodeResult::Type UChase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIOwner = OwnerComp.GetAIOwner();
	APawn* OwnerPawn = AIOwner->GetPawn();

	if (AIOwner)
	{
		FVector TargetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());
		FVector Direction = (TargetLocation - OwnerPawn->GetActorLocation()).GetSafeNormal();

		TargetLocation = TargetLocation - (Direction * StopDistance);

		UAIBlueprintHelperLibrary::SimpleMoveToLocation(AIOwner, TargetLocation);

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	
	}
	return EBTNodeResult::Failed;
}
