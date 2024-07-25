// Fill out your copyright notice in the Description page of Project Settings.


#include "Turn_Rootmotion.h"

#include "AIController.h"
#include "Enemy_Base.h"

UTurn_Rootmotion::UTurn_Rootmotion(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("TurnAround");
}

EBTNodeResult::Type UTurn_Rootmotion::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIOwner = OwnerComp.GetAIOwner();
	APawn* OwnerPawn = AIOwner->GetPawn();

	AEnemy_Base* Enemy = Cast<AEnemy_Base>(OwnerPawn);

	Enemy->TurnAround();
	
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
