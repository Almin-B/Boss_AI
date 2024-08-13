// Fill out your copyright notice in the Description page of Project Settings.


#include "FollowWalkingPathComponent.h"

// Sets default values for this component's properties
UFollowWalkingPathComponent::UFollowWalkingPathComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UFollowWalkingPathComponent::UpdateOwnerRotation()
{
	
	if(Owner)
	{
		Owner->SetActorRotation(GetSplineRotation());
	}
}

void UFollowWalkingPathComponent::SetIsUpdateActive(bool isActive)
{
	bIsUpdateActive = isActive;
}

FRotator UFollowWalkingPathComponent::GetSplineRotation()
{
	FRotator Rotation;
	

	float OwnerSplineDistance = WalkingPathReference->WalkingPathSpline->GetDistanceAlongSplineAtLocation(GetOwnerLocation(),ESplineCoordinateSpace::World);
	Rotation = FRotator(Owner->GetActorRotation().Pitch,WalkingPathReference->WalkingPathSpline->GetRotationAtDistanceAlongSpline(OwnerSplineDistance,ESplineCoordinateSpace::World).Yaw,Owner->GetActorRotation().Roll);
	
	if(Owner->GetActorForwardVector().X < 0.0f)
	{
		Rotation += FRotator(0,180,0);
	}
	return Rotation;
}

FVector UFollowWalkingPathComponent::GetOwnerLocation()
{
	FVector Location;
	if(Owner)
	{
		Location = Owner->GetActorLocation();
	}
	return Location;
}

void UFollowWalkingPathComponent::SnapOwnerToPath()
{
	if(Owner)
	{
		float OwnerSplineDistance = WalkingPathReference->WalkingPathSpline->GetDistanceAlongSplineAtLocation(GetOwnerLocation(),ESplineCoordinateSpace::World);
		float SnapLocY = WalkingPathReference->WalkingPathSpline->GetLocationAtDistanceAlongSpline(OwnerSplineDistance,ESplineCoordinateSpace::World).Y;
		SnapLocY += LineOffset;
		FVector SnapLocation = FVector(Owner->GetActorLocation().X,SnapLocY,Owner->GetActorLocation().Z);

		Owner->SetActorLocation(SnapLocation);
	}
}


// Called when the game starts
void UFollowWalkingPathComponent::BeginPlay()
{
	Super::BeginPlay();
	if(WalkingPathReference)
	{
		Owner = Cast<APawn>(this->GetOwner());
	}
	// ...
	
}


// Called every frame
void UFollowWalkingPathComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(WalkingPathReference)
	{
		if(bIsUpdateActive)
		{
			UpdateOwnerRotation();
		}
		if(bSnapToPath)
		{
			SnapOwnerToPath();
		}
	}
	// ...
}

