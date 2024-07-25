// Fill out your copyright notice in the Description page of Project Settings.


#include "ChangeMovementState.h"


UChangeMovementState::UChangeMovementState(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("ChangeMovementState");
}

EBTNodeResult::Type UChangeMovementState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIOwner = OwnerComp.GetAIOwner();
	APawn* OwnerPawn = AIOwner->GetPawn();

	AEnemy_Base* Enemy = Cast<AEnemy_Base>(OwnerPawn);

	if(Enemy->bIsRootmotionEnabled)
	{
		Enemy->ChangeRootmotionState(SetMovementState);
	}
	else
	{
		Enemy->CurrentMovemntState = SetMovementState;
		Enemy->UpdateMovementState();
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
