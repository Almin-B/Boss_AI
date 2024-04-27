// Fill out your copyright notice in the Description page of Project Settings.


#include "ChooseCloseCombatAttack.h"

UChooseCloseCombatAttack::UChooseCloseCombatAttack(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("ChooseCloseCombatAttack");
}

EBTNodeResult::Type UChooseCloseCombatAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	AAIController* AIOwner = OwnerComp.GetAIOwner();
	APawn* OwnerPawn = AIOwner->GetPawn();

	ALanceFighter* Enemy = Cast<ALanceFighter>(OwnerPawn);

	if (Enemy)
	{

		OwnerComp.GetBlackboardComponent()->SetValueAsInt(GetSelectedBlackboardKey(),Enemy->ChooseCombatAttack(Enemy->CloseCombatProbabilities));


		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	else
	{
		return EBTNodeResult::Failed;
	}
}
