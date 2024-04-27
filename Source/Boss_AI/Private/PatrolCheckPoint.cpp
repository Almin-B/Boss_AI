// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolCheckPoint.h"

// Sets default values
APatrolCheckPoint::APatrolCheckPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APatrolCheckPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APatrolCheckPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

