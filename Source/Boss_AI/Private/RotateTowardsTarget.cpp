// Fill out your copyright notice in the Description page of Project Settings.


#include "RotateTowardsTarget.h"

URotateTowardsTarget::URotateTowardsTarget(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("RotateTowardsTarget");

}

EBTNodeResult::Type URotateTowardsTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIOwner = OwnerComp.GetAIOwner();
	APawn* OwnerPawn = AIOwner->GetPawn();

	if (OwnerPawn)
	{
		FVector TargetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());
		FVector EnemyLocation = OwnerPawn->GetActorLocation();

		FRotator EnemyRotation = OwnerPawn->GetActorRotation();

		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(EnemyLocation, TargetLocation);

		FRotator NewRotation = FMath::RInterpTo(OwnerPawn->GetActorRotation(), FRotator(EnemyRotation.Pitch, LookAtRotation.Yaw, LookAtRotation.Roll), 1, RotationSpeed);

		OwnerPawn->SetActorRotation(NewRotation);

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;

	}
	else
	{
		return EBTNodeResult::Failed;
	}
}
