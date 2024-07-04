// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_2D.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"

void APlayer_2D::DetectMoveDirection(float AxisValue)
{
	if(CurrentMoveDirectionAlpha > 0.1f)
	{
		if(AxisValue < -0.1)
		{
			Turn();
			CurrentMoveDirectionAlpha = -1;
		}
	}
	else if(CurrentMoveDirectionAlpha < -0.1f)
	{
		if(AxisValue > 0.1)
		{
			Turn();
			CurrentMoveDirectionAlpha = 1;
		}
	}
}

void APlayer_2D::Turn()
{
	
	bIsTurning = true;
	DisableInput(UGameplayStatics::GetPlayerController(GetWorld(),0));
	MoveRightAxisValue = 0;
	this->GetCharacterMovement()->StopMovementImmediately();
}
