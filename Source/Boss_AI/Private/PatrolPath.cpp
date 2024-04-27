// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolPath.h"

// Sets default values
APatrolPath::APatrolPath()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

FVector APatrolPath::GetPatrolPointLocation()
{
	FVector TargetPatrolPointLocation;

	if (PatrolPoints.Num() > 0)
	{
		TargetPatrolPointLocation = PatrolPoints[PatrolPointIndex];

		PatrolPointIndex++;

		if (PatrolPointIndex == PatrolPoints.Num())
		{
			PatrolPointIndex = 0;
		}

	}
	
	return TargetPatrolPointLocation;
}

// Called when the game starts or when spawned
void APatrolPath::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APatrolPath::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

