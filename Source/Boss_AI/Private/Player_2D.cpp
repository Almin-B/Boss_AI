// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_2D.h"

#include "HeavyAttackEnd.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "HeavyAttackFollowUpNotify.h"

void APlayer_2D::DetectMoveDirection(float AxisValue)
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

void APlayer_2D::Turn()
{
	if(!bIsTurning && !bIsSprinting && !bIsInHeavyAttack && !bIsAttacking)
	{
		bIsTurning = true;
		DisableInput(UGameplayStatics::GetPlayerController(GetWorld(),0));
		MoveRightAxisValue = 0;
		this->GetCharacterMovement()->StopMovementImmediately();
	}
}

float APlayer_2D::GetCurrentMoveDirectionAlpha()
{
	float XDirection = this->GetActorForwardVector().X;
	
	return XDirection;
}

void APlayer_2D::HeavyAttackFollowup()
{
	if(HeavyAttack_FollowUp_Montage && bIsAttacking)
	{
		this->GetMesh()->GetAnimInstance()->Montage_Play(HeavyAttack_FollowUp_Montage,AttackSpeed);
	}
}

void APlayer_2D::HeavyAttack_Implementation()
{
	Super::HeavyAttack_Implementation();

	if(HeavyAttackMontage && !bIsAttacking && !bIsInHeavyAttack)
	{
		bIsAttacking = true;
		bIsInHeavyAttack = true;
		this->GetMesh()->GetAnimInstance()->Montage_Play(HeavyAttackMontage,AttackSpeed);
	}
	
}

void APlayer_2D::InitHeavyAttackNotify()
{
	if(HeavyAttackMontage)
	{
			for (FAnimNotifyEvent EventNotify : HeavyAttackMontage->Notifies)
			{
				if (const auto HeavyAttackNotify = Cast<UHeavyAttackFollowUpNotify>(EventNotify.Notify))
				{
					HeavyAttackNotify->OnNotified.AddUObject(this, &APlayer_2D::HeavyAttackFollowup);
				}
				if(const auto HeavyAttackEndNotify = Cast<UHeavyAttackEnd>(EventNotify.Notify))
				{
					HeavyAttackEndNotify->OnNotified.AddUObject(this, &APlayer_2D::OnHeavyAttackEnd);
				}
			}
	}
	if(HeavyAttack_FollowUp_Montage)
	{
		for (FAnimNotifyEvent EventNotify : HeavyAttack_FollowUp_Montage->Notifies)
		{
			if(const auto HeavyAttackEndNotify = Cast<UHeavyAttackEnd>(EventNotify.Notify))
			{
				HeavyAttackEndNotify->OnNotified.AddUObject(this, &APlayer_2D::OnHeavyAttackEnd);
			}
		}
	}
}

void APlayer_2D::OnHeavyAttackEnd()
{
	bIsInHeavyAttack = false;
}

void APlayer_2D::BeginPlay()
{
	Super::BeginPlay();
	InitHeavyAttackNotify();
}

void APlayer_2D::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}
