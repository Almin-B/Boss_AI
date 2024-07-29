// Fill out your copyright notice in the Description page of Project Settings.


#include "ExecuteAttack_Task.h"

#include "AIController.h"
#include "Raccoon.h"

UExecuteAttack::UExecuteAttack(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("ExecuteAttack_Task");
}

EBTNodeResult::Type UExecuteAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIOwner = OwnerComp.GetAIOwner();
	APawn* OwnerPawn = AIOwner->GetPawn();

	AEnemy_Base* Enemy = Cast<AEnemy_Base>(OwnerPawn);

	Enemy->StartAttack(AttackName);
	
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
