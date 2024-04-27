// Fill out your copyright notice in the Description page of Project Settings.


#include "FollowUpDefenseAttack.h"

UFollowUpDefenseAttack::UFollowUpDefenseAttack(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("FollowUpDefenseAttackProbability");
}

EBTNodeResult::Type UFollowUpDefenseAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	float RandValue;

	RandValue = FMath::RandRange(0.0f, 100.0f);


	if (FollowUpProbability >= RandValue)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(FName("DoFollowUp"), true);
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(FName("DoFollowUp"), false);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(FName("IsDefense"), false);
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
