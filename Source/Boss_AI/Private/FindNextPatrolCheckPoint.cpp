// Fill out your copyright notice in the Description page of Project Settings.


#include "FindNextPatrolCheckPoint.h"


UFindNextPatrolCheckPoint::UFindNextPatrolCheckPoint(FObjectInitializer const& ObjectInitializer)
{
}

EBTNodeResult::Type UFindNextPatrolCheckPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIOwner = OwnerComp.GetAIOwner();
	APawn* OwnerPawn = AIOwner->GetPawn();

	AEnemy_Base* Enemy = Cast<AEnemy_Base>(OwnerPawn);
	FVector NextPatrolPointLocation;

	if(Enemy)
	{
		if (Enemy->PatrolPath)
		{
			//Relative PatrolPoint Location
			NextPatrolPointLocation = Enemy->PatrolPath->GetPatrolPointLocation();
			//Transform to Global Location
			FVector GlobalPatrolPointLocation = Enemy->PatrolPath->GetActorTransform().TransformPosition(NextPatrolPointLocation);

			OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), GlobalPatrolPointLocation);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;
		}
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), NextPatrolPointLocation);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}
