// Fill out your copyright notice in the Description page of Project Settings.


#include "Raccoon.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"


void ARaccoon::ArenaDash()
{
	if(bIsFlyState)
	{
		FHitResult Hit;
		FVector Start = this->GetActorLocation();
		FVector End = this->GetActorLocation() + (this->GetActorForwardVector() * 10000);
		FCollisionQueryParams TraceParams = FCollisionQueryParams(FName(TEXT("Trace")), true, this);
		TraceParams.bTraceComplex = false;
		TraceParams.bReturnPhysicalMaterial = false;

		GetWorld()->LineTraceSingleByChannel(Hit,Start,End,ECC_WorldStatic,TraceParams);

		if (Hit.bBlockingHit)
		{
			if (bShowDashDebug)
			{
				DrawDebugLine(GetWorld(),Start,Hit.Location,FColor::Yellow,false,2,0,12);
				DrawDebugSphere(GetWorld(), Hit.Location, 25, 12, FColor::Orange, false, 2, 0, 10);
			}

			DashStart = Start;
			DashEnd = Hit.Location - (this->GetActorForwardVector() * ArenaWallOffset);
			DashTimeline.PlayFromStart();
		}
	}

}

void ARaccoon::AktivateFlyState()
{
	InitArenaDashTimeline();
	InitFlyingPhase();
}

void ARaccoon::InitArenaDashTimeline()
{
	if (DashAlpha && DashAlphaZ)
	{
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindUFunction(this, FName("ArenaDashProgress"));
		DashTimeline.AddInterpFloat(DashAlpha, TimelineProgress);
		DashTimeline.SetLooping(false);
		DashTimeline.SetPlayRate(DashSpeed);
		
	}
}

void ARaccoon::InitFlyingPhase()
{
	FlyHeight = this->GetActorLocation().Z;
	bIsFlyState = true;

	this->GetController()->FindComponentByClass<UBlackboardComponent>()->SetValueAsBool(FName("IsFlystate"), bIsFlyState);

	
}


void ARaccoon::ArenaDashProgress(float Value)
{
	FVector NewLocation = FMath::Lerp(DashStart, DashEnd, Value);
	NewLocation.Z = FlyHeight + (DashHeightOffset * DashAlphaZ->GetFloatValue(Value));

	this->SetActorLocation(NewLocation);

	FlyAnimSpeed = FMath::Lerp(1.0f, MaxDashAnimSpeed, FMath::Abs(DashAlphaZ->GetFloatValue(Value)));
	DashAnimAlpha = FMath::Lerp(1.0f, 0.0f, FMath::Abs(DashAlphaZ->GetFloatValue(Value)));

	
}

void ARaccoon::BeginPlay()
{
	Super::BeginPlay();
}

void ARaccoon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DashTimeline.TickTimeline(DeltaTime);
}
