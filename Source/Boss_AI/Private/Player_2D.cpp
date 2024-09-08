// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_2D.h"

#include "HeavyAttackEnd.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "HeavyAttackFollowUpNotify.h"
#include "IActionRecive.h"
#include "LanceFighter.h"
#include "MontageEndNotify.h"
#include "SpawnCloseCombatHitboxNotify.h"
#include "Components/CapsuleComponent.h"

APlayer_Guts_2D::APlayer_Guts_2D()
{
	FollowWalkingPath = CreateDefaultSubobject<UFollowWalkingPathComponent>(TEXT("FollowWalkingPathComponent"));
	InventoryComp = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
}

void APlayer_Guts_2D::DetectMoveDirection(float AxisValue)
{
	if(GetCurrentMoveDirectionAlpha() > 0.1f)
	{
		if(AxisValue < -0.1)
		{
			Turn();
		}
	}
	else if(GetCurrentMoveDirectionAlpha() < -0.1f)
	{
		if(AxisValue > 0.1)
		{
			Turn();
		}
	}
}

void APlayer_Guts_2D::Turn()
{
	//if(CanTurn() && TurnAnimation)
	//{
	//	if(!GetWorldTimerManager().IsTimerActive(TurnTimerHandle))
	//	{
	//		bIsTurning = true;
	//		DisableInput(UGameplayStatics::GetPlayerController(GetWorld(),0));
	//		MoveRightAxisValue = 0;
	//		this->GetCharacterMovement()->StopMovementImmediately();
	//		FollowWalkingPath->SetIsUpdateActive(false);
	//	
	//		TurnDuration = TurnAnimation->GetPlayLength() / TurnRate;
	//		GetWorldTimerManager().SetTimer(TurnTimerHandle,this,&APlayer_2D::OnTurnEnd,TurnDuration,false);
	//	}
	//}
	if(CanTurn())
	{
		this->SetActorRotation(this->GetActorRotation() + FRotator(0,180,0));
	}
}

float APlayer_Guts_2D::GetCurrentMoveDirectionAlpha()
{
	float XDirection = this->GetActorForwardVector().X;
	
	return XDirection;
}

bool APlayer_Guts_2D::CanTurn()
{
	if(!bIsTurning && !bIsSprinting && !bIsInHeavyAttack && !bIsAttacking && !bIsRolling && !bIsInLightAttack && !bIsInSpecialAttack)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool APlayer_Guts_2D::CanRoll()
{
	if(!bIsRolling && RollMontage && !bIsTurning && !bIsAttacking && !bIsInHeavyAttack && !bIsInLightAttack && !bIsInSpecialAttack)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void APlayer_Guts_2D::OnTurnEnd()
{
	bIsTurning = false;
	FollowWalkingPath->SetIsUpdateActive(true);
	
	EnableInput(UGameplayStatics::GetPlayerController(GetWorld(),0));
	
	GetWorldTimerManager().ClearTimer(TurnTimerHandle);
}

void APlayer_Guts_2D::InitMovementNotifys()
{
	if(RollMontage)
	{
		for (FAnimNotifyEvent EventNotify : RollMontage->Notifies)
		{
			if(const auto RollEndNotify = Cast<UMontageEndNotify>(EventNotify.Notify))
			{
				RollEndNotify->OnNotified.AddUObject(this, &APlayer_Guts_2D::OnRollEnd);
			}
		}
	}
}

void APlayer_Guts_2D::Roll()
{
	if(CanRoll())
	{
		bIsRolling = true;
		this->GetMesh()->GetAnimInstance()->Montage_Play(RollMontage,RollSpeed);
		this->GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel1,ECR_Ignore);
	}
}

void APlayer_Guts_2D::OnRollEnd()
{
	bIsRolling = false;
	this->GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel1,ECR_Block);
}

void APlayer_Guts_2D::BeginPlay()
{
	Super::BeginPlay();
	InitMovementNotifys();
}

void APlayer_Guts_2D::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}
