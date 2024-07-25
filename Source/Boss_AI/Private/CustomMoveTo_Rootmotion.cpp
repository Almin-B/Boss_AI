// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomMoveTo_Rootmotion.h"

#include "AIController.h"
#include "Enemy_Base.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

UCustomMoveTo_Rootmotion::UCustomMoveTo_Rootmotion(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("CustomMoveTo_Rootmotion");
}

EBTNodeResult::Type UCustomMoveTo_Rootmotion::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIOwner = OwnerComp.GetAIOwner();
	APawn* OwnerPawn = AIOwner->GetPawn();

	AEnemy_Base* Enemy = Cast<AEnemy_Base>(OwnerPawn);

	float Distance = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(DistanceToTarget.SelectedKeyName);

	//><
	if(Distance >= 0)
	{
		Enemy->ChangeRootmotionState(EMovemntState::Walk);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("InProgress Distance: %f"), Distance));
		
	}
	else
	{
		Enemy->ChangeRootmotionState(EMovemntState::Idle);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Finished")));
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

