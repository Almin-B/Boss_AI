// Fill out your copyright notice in the Description page of Project Settings.


#include "FollowPlayerProcessor.h"
#include "FollowPlayerTrait.h"
#include "MassCommonTypes.h"
#include "MassCommonFragments.h"
#include "MassExecutionContext.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

UFollowPlayerProcessor::UFollowPlayerProcessor():EntityQuery(*this)
{
	bAutoRegisterWithProcessingPhases = true;
	ExecutionFlags = (int32)EProcessorExecutionFlags::All;
	ExecutionOrder.ExecuteBefore.Add(UE::Mass::ProcessorGroupNames::Avoidance);
}

void UFollowPlayerProcessor::ConfigureQueries()
{
	EntityQuery.AddRequirement<FTransformFragment>(EMassFragmentAccess::ReadWrite);
	EntityQuery.AddRequirement<FFollowPlayerFragment>(EMassFragmentAccess::ReadWrite);
}

void UFollowPlayerProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	AActor* PlayerActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (!PlayerActor) return;
	
	const FVector PlayerLocation = PlayerActor->GetActorLocation();
	
	EntityQuery.ForEachEntityChunk(EntityManager, Context, ([this, PlayerLocation](FMassExecutionContext& Context)
	{
		const TArrayView<FTransformFragment> TransformList = Context.GetMutableFragmentView<FTransformFragment>();
		const TArrayView<FFollowPlayerFragment> SimpleMovementsList = Context.GetMutableFragmentView<FFollowPlayerFragment>();
		const float WorldDeltaTime = Context.GetDeltaTimeSeconds();
		
		for(int32 EntityIndex = 0; EntityIndex < Context.GetNumEntities(); ++EntityIndex)
		{

			const FFollowPlayerFragment& FollowPlayerFragment = SimpleMovementsList[EntityIndex];
			
			float FollowDistance = SimpleMovementsList[EntityIndex].FragmentFollowDistance;
			
			FTransform& Transform = TransformList[EntityIndex].GetMutableTransform();
			FVector& MoveTarget = SimpleMovementsList[EntityIndex].TargetLocation;
			FRotator& MoveRotation = SimpleMovementsList[EntityIndex].TargetRotation;
	
			//Location
			const FVector CurrentLocation = Transform.GetLocation();
			const FVector DirectionToPlayer = (PlayerLocation - CurrentLocation).GetSafeNormal();
			const FVector DesiredLocation = PlayerLocation - DirectionToPlayer * FollowDistance;

			FVector AvoidForce = FVector(0,0,0);
			
			for(int32 OtherIndex = 0; OtherIndex < Context.GetNumEntities(); ++OtherIndex)
			{
				if(OtherIndex != EntityIndex)
				{
					FVector OtherLocation = TransformList[OtherIndex].GetTransform().GetLocation();
					float Distance = (CurrentLocation - OtherLocation).Size();
			
					if(Distance < FollowPlayerFragment.FragmentAvoidDistance)
					{
						FVector Diff = CurrentLocation - OtherLocation;
						AvoidForce += Diff.GetSafeNormal() / Distance;
					}
				}
			}

			// Update target
			MoveTarget = FVector(DesiredLocation.X,DesiredLocation.Y,DesiredLocation.Z);

			MoveTarget += AvoidForce * FollowPlayerFragment.FragmentAvoidPower;

			MoveTarget.Z = 0.0f;
			
		
			// Move toward target
			const FVector ToTarget = MoveTarget - CurrentLocation;

			if (ToTarget.Size() > FollowPlayerFragment.FragmentFollowThreshhold)
			{
				if (ToTarget.Size() > FollowPlayerFragment.FragmentFollowThreshhold + 20.0f)
				{
					SimpleMovementsList[EntityIndex].bIsMoving = true;
				}
				else
				{
					SimpleMovementsList[EntityIndex].bIsMoving = false;
				}


				const FVector SmoothedLocation = FMath::VInterpTo(CurrentLocation, MoveTarget, WorldDeltaTime, FollowPlayerFragment.FragmentMovementInterpSpeed); // 2.0f = move smoothing speed
				Transform.SetLocation(SmoothedLocation);
				
				// --- Calculate smooth rotation ---
				const FRotator CurrentRotator = Transform.GetRotation().Rotator();
				FRotator DesiredRotator = UKismetMathLibrary::FindLookAtRotation(CurrentLocation, MoveTarget);
				DesiredRotator.Pitch = 0.0f;
				DesiredRotator.Roll = 0.0f;
	
				// Interpolate to desired rotation
				const FRotator SmoothRotation = FMath::RInterpTo(CurrentRotator, DesiredRotator, WorldDeltaTime, FollowPlayerFragment.FragmentRotationInterpSpeed); // 5.0f = turn speed
				Transform.SetRotation(FQuat(SmoothRotation));
	
				// Store for debugging or external use
				MoveRotation = SmoothRotation;
			}
			else
			{
				SimpleMovementsList[EntityIndex].bIsMoving = false;
			}
			
		}
	
	}));
}
