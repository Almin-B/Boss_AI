// Fill out your copyright notice in the Description page of Project Settings.


#include "DecideToExitDefense.h"

UDecideToExitDefense::UDecideToExitDefense(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("DecideToExitBlock");
}

EBTNodeResult::Type UDecideToExitDefense::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIOwner = OwnerComp.GetAIOwner();
	APawn* OwnerPawn = AIOwner->GetPawn();

	ALanceFighter* Enemy = Cast<ALanceFighter>(OwnerPawn);
	APlayer_Base* Player = Cast<APlayer_Base>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if(Enemy && Player)
	{
		if (Player->bIsAttacking)
		{
			//OwnerComp.GetBlackboardComponent()->SetValueAsBool(FName("IsDefense"), true);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(FName("IsBlocking"), true);
			Enemy->bIsBlocking = true;
		}
		else
		{
			//OwnerComp.GetBlackboardComponent()->SetValueAsBool(FName("IsDefense"), false);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(FName("IsBlocking"), false);
			Enemy->bIsBlocking = false;
		}
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
