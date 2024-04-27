// Fill out your copyright notice in the Description page of Project Settings.


#include "AbortCurrentAttackMontage.h"

UAbortCurrentAttackMontage::UAbortCurrentAttackMontage(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("AbortCurrentAttackMontage");
}

EBTNodeResult::Type UAbortCurrentAttackMontage::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIOwner = OwnerComp.GetAIOwner();
	APawn* OwnerPawn = AIOwner->GetPawn();

	ALanceFighter* Enemy = Cast<ALanceFighter>(OwnerPawn);

	if (Enemy)
	{
		Enemy->StopCurrentPlayedAttackAnimMontage();
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
