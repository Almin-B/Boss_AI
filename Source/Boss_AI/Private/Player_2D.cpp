// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_2D.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"

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
	if(!bIsTurning && !bIsSprinting)
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
