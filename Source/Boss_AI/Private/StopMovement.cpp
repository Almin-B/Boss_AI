// Fill out your copyright notice in the Description page of Project Settings.


#include "StopMovement.h"

UStopMovement::UStopMovement(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("StopMovement");

}

EBTNodeResult::Type UStopMovement::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIOwner = OwnerComp.GetAIOwner();
	APawn* OwnerPawn = AIOwner->GetPawn();

	if(AIOwner)
	{
		AIOwner->StopMovement();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	else
	{
		return EBTNodeResult::Failed;
		
	}
}
