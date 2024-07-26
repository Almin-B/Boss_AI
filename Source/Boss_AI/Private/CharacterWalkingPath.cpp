// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterWalkingPath.h"

// Sets default values
ACharacterWalkingPath::ACharacterWalkingPath()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WalkingPathSpline = CreateDefaultSubobject<USplineComponent>(TEXT("WalkingSpline"));
	WalkingPathSpline->SetupAttachment(RootComponent);
	WalkingPathSpline->SetClosedLoop(bIsLoopedPath);

}

void ACharacterWalkingPath::CreateWalkingPathSpline()
{
	WalkingPathSpline->ClearSplinePoints(true);
	for (auto checkpoint : CheckPoints)
	{
		WalkingPathSpline->AddSplinePoint(checkpoint,ESplineCoordinateSpace::Local,true);
	}
}

// Called when the game starts or when spawned
void ACharacterWalkingPath::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACharacterWalkingPath::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

