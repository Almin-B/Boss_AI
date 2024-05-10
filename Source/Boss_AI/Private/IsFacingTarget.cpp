// Fill out your copyright notice in the Description page of Project Settings.


#include "IsFacingTarget.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

UIsFacingTarget::UIsFacingTarget()
{
}

void UIsFacingTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

	AAIController* AIOwner = OwnerComp.GetAIOwner();
	APawn* OwnerPawn = AIOwner->GetPawn();

	if (OwnerPawn)
	{
		FVector EnemyFacing = OwnerPawn->GetActorForwardVector(); 
		FVector TargetFacing = UKismetMathLibrary::GetForwardVector(UKismetMathLibrary::FindLookAtRotation(OwnerPawn->GetActorLocation(), OwnerComp.GetBlackboardComponent()->GetValueAsVector(TargetLocation.SelectedKeyName)));
		float FacingAlpha = UKismetMathLibrary::Dot_VectorVector(EnemyFacing, TargetFacing);
		if (UKismetMathLibrary::DegAcos(FacingAlpha) > ViewAngle)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(IsFacing.SelectedKeyName, false);
		}
		else
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(IsFacing.SelectedKeyName, true);
		}
	}
}
