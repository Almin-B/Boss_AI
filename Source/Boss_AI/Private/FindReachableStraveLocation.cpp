// Fill out your copyright notice in the Description page of Project Settings.


#include "FindReachableStraveLocation.h"


UFindReachableStraveLocation::UFindReachableStraveLocation(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("FindReachableStraveLocation");
}

EBTNodeResult::Type UFindReachableStraveLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIOwner = OwnerComp.GetAIOwner();
	APawn* OwnerPawn = AIOwner->GetPawn();

	FVector TargetStraveLocation;
    FVector StraveDistance;

	StraveDistance = (OwnerPawn->GetActorRightVector() * FMath::RandRange(MinStraveDistance, MaxStraveDistance));

	if(FMath::RandBool())
	{
		StraveDistance *= -1;
	}

	TargetStraveLocation = OwnerPawn->GetActorLocation() + StraveDistance;

	OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), TargetStraveLocation);
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;


}
