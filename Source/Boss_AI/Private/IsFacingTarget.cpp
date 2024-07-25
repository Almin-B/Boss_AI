// Fill out your copyright notice in the Description page of Project Settings.


#include "IsFacingTarget.h"

#include "AIController.h"
#include "Enemy_Base.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

UIsFacingTarget::UIsFacingTarget()
{
}

void UIsFacingTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

	AAIController* AIOwner = OwnerComp.GetAIOwner();
	APawn* OwnerPawn = AIOwner->GetPawn();

	AEnemy_Base* Enemy = Cast<AEnemy_Base>(OwnerPawn);

	if (Enemy)
	{
		FVector Location = OwnerComp.GetBlackboardComponent()->GetValueAsVector(TargetLocation.SelectedKeyName);
		bool bIsFacing = Enemy->IsLookingAt(Location,ViewAngle);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(IsFacing.SelectedKeyName, bIsFacing);
	}
}
