// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_02.h"

#include "Kismet/KismetMathLibrary.h"

APlayer_02::APlayer_02()
{
	HitBoxSpawnPoint = CreateDefaultSubobject<USphereComponent>(TEXT("HitBoxSpawnPoint"));
	HitBoxSpawnPoint->SetupAttachment(this->GetMesh());
	HitBoxSpawnPoint->SetSphereRadius(2.0f);
	InventoryComp = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
}

void APlayer_02::AddRootmotionMovementInput(float ForwardAxisValue, float RightAxisValue, float MovementThreshold)
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

void APlayer_02::OrientRotationToRootmotion(float ForwardAxisValue, float RightAxisValue,float MovementThreshold)
{
	if(ForwardAxisValue < -MovementThreshold || ForwardAxisValue > MovementThreshold || RightAxisValue < -MovementThreshold || RightAxisValue > MovementThreshold)
	{
		FVector RootmotionVector = FVector(ForwardAxisValue,RightAxisValue,0.0f);
		FRotator DesiredRotation = FMath::RInterpTo(NewOrientRotation,UKismetMathLibrary::MakeRotFromX(RootmotionVector),GetWorld()->DeltaTimeSeconds,10.0f);
		NewOrientRotation = DesiredRotation;
		this->SetActorRotation(NewOrientRotation);
	}
}

void APlayer_02::BeginPlay()
{
	Super::BeginPlay();
}

void APlayer_02::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
