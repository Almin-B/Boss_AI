// Fill out your copyright notice in the Description page of Project Settings.


#include "Raccoon.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


ARaccoon::ARaccoon()
{
	FollowWalkingPath = CreateDefaultSubobject<UFollowWalkingPathComponent>(TEXT("FollowWalkingPathComponent"));
}

void ARaccoon::TurnAround()
{
	Super::TurnAround();
	FollowWalkingPath->SetIsUpdateActive(false);
}

void ARaccoon::TurnEndCallback()
{
	Super::TurnEndCallback();
	FollowWalkingPath->SetIsUpdateActive(true);
}

void ARaccoon::BeginPlay()
{
	Super::BeginPlay();
	UpdateMovementState();
}

void ARaccoon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
