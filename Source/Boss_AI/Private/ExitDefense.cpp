// Fill out your copyright notice in the Description page of Project Settings.


#include "ExitDefense.h"

UExitDefense::UExitDefense(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("ExitDefense");

}

EBTNodeResult::Type UExitDefense::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIOwner = OwnerComp.GetAIOwner();
	APawn* OwnerPawn = AIOwner->GetPawn();

	ALanceFighter* Enemy = Cast<ALanceFighter>(OwnerPawn);

	if (Enemy)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(FName("IsDefense"), false);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(FName("IsBlocking"), false);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(FName("DoFollowUp"), false);
		Enemy->bIsBlocking = false;
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
