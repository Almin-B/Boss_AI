// Fill out your copyright notice in the Description page of Project Settings.


#include "ChooseLongRangeCombatAttack.h"

UChooseLongRangeCombatAttack::UChooseLongRangeCombatAttack(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("ChooseLongRangeCombatAttack");
}

EBTNodeResult::Type UChooseLongRangeCombatAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIOwner = OwnerComp.GetAIOwner();
	APawn* OwnerPawn = AIOwner->GetPawn();

	ALanceFighter* Enemy = Cast<ALanceFighter>(OwnerPawn);

	if (Enemy)
	{

		OwnerComp.GetBlackboardComponent()->SetValueAsInt(GetSelectedBlackboardKey(), Enemy->ChooseCombatAttack(Enemy->LongCombatProbabilities));


		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	else
	{
		return EBTNodeResult::Failed;
	}
}
