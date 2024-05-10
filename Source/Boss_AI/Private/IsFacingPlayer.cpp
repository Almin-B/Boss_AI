// Fill out your copyright notice in the Description page of Project Settings.


#include "IsFacingPlayer.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

UIsFacingPlayer::UIsFacingPlayer()
{
}

void UIsFacingPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	AAIController* AIOwner = OwnerComp.GetAIOwner();
	APawn* OwnerPawn = AIOwner->GetPawn();

	if (Player && OwnerPawn)
	{
		FVector EnemyFacing = OwnerPawn->GetActorForwardVector(); 
		FVector PlayerFacing = UKismetMathLibrary::GetForwardVector(UKismetMathLibrary::FindLookAtRotation(OwnerPawn->GetActorLocation(), Player->GetActorLocation()));
		float FacingAlpha = UKismetMathLibrary::Dot_VectorVector(EnemyFacing, PlayerFacing);
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

