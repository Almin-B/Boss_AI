// Fill out your copyright notice in the Description page of Project Settings.


#include "ChooseCombatStyle.h"

UChooseCombatStyle::UChooseCombatStyle(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("ChooseCombatStyle");
}

EBTNodeResult::Type UChooseCombatStyle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIOwner = OwnerComp.GetAIOwner();
	APawn* OwnerPawn = AIOwner->GetPawn();

	ALanceFighter* Enemy = Cast<ALanceFighter>(OwnerPawn);

	if (Enemy)
	{
		bool bUseLongRange;

		if (Enemy->ChooseCombatAttack(Enemy->CombatProbabilities) == 1)
		{
			bUseLongRange = true;
		}
		else
		{
			bUseLongRange = false;
		}

		OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), bUseLongRange);


		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	else
	{
		return EBTNodeResult::Failed;
	}
}
