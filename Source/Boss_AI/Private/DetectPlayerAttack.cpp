// Fill out your copyright notice in the Description page of Project Settings.


#include "DetectPlayerAttack.h"

UDetectPlayerAttack::UDetectPlayerAttack()
{
	NodeName = TEXT("DetectPlayerAttack");
}

void UDetectPlayerAttack::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* AIOwner = OwnerComp.GetAIOwner();
	APawn* OwnerPawn = AIOwner->GetPawn();

	ALanceFighter* Enemy = Cast<ALanceFighter>(OwnerPawn);

	if (Enemy)
	{
		if(!OwnerComp.GetBlackboardComponent()->GetValueAsBool(FName("DoFollowUp")))
		{

			float DistanceToTarget = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(Distance.SelectedKeyName);
			if (DistanceToTarget < MinDistanceToTarget)
			{
				if (Enemy->DetectPlayerAttack() && OwnerComp.GetBlackboardComponent()->GetValueAsBool(IsFaceingPlayer.SelectedKeyName))
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsBool(IsDefense.SelectedKeyName, true);
					OwnerComp.GetBlackboardComponent()->SetValueAsBool(IsBlocking.SelectedKeyName, true);

					Enemy->bIsBlocking = true;
				}
			}
		}

	}
}
