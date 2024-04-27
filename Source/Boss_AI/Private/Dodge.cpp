// Fill out your copyright notice in the Description page of Project Settings.


#include "Dodge.h"

UDodge::UDodge(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Dodge");
}

EBTNodeResult::Type UDodge::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIOwner = OwnerComp.GetAIOwner();
	APawn* OwnerPawn = AIOwner->GetPawn();

	AEnemy_Base* Enemy = Cast<AEnemy_Base>(OwnerPawn);

	Enemy->Dodge(DodgeDirection);

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
