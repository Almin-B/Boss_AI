// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_02.h"

#include "Kismet/KismetMathLibrary.h"

APlayer_Guts_3D::APlayer_Guts_3D()
{
	InventoryComp = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
}

void APlayer_Guts_3D::AddRootmotionMovementInput(float ForwardAxisValue, float RightAxisValue, float MovementThreshold)
{
	if(ForwardAxisValue < -MovementThreshold || ForwardAxisValue > MovementThreshold || RightAxisValue < -MovementThreshold || RightAxisValue > MovementThreshold)
	{
		MoveForwardAxisValue = this->GetActorForwardVector().Length();
	}
	else
	{
		MoveForwardAxisValue = 0.0f;
	}
}

void APlayer_Guts_3D::OrientRotationToRootmotion(float ForwardAxisValue, float RightAxisValue,float MovementThreshold)
{
	if(ForwardAxisValue < -MovementThreshold || ForwardAxisValue > MovementThreshold || RightAxisValue < -MovementThreshold || RightAxisValue > MovementThreshold)
	{
		FVector RootmotionVector = FVector(ForwardAxisValue,RightAxisValue,0.0f);
		FRotator DesiredRotation = FMath::RInterpTo(NewOrientRotation,UKismetMathLibrary::MakeRotFromX(RootmotionVector),GetWorld()->DeltaTimeSeconds,10.0f);
		NewOrientRotation = DesiredRotation;
		this->SetActorRotation(NewOrientRotation);
	}
}

void APlayer_Guts_3D::BeginPlay()
{
	Super::BeginPlay();
}

void APlayer_Guts_3D::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
