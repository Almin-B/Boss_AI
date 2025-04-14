// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpAttackProcessor.h"
#include "MassExecutionContext.h"
#include "JumpAttackTrait.h"
#include "Kismet/GameplayStatics.h"
#include "MassCommonFragments.h"

UJumpAttackProcessor::UJumpAttackProcessor():EntityQuery(*this)
{
	bAutoRegisterWithProcessingPhases = true;
	ExecutionFlags = (int32)EProcessorExecutionFlags::All;
	ExecutionOrder.ExecuteAfter.Add(TEXT("FollowPlayerProcessor"));
}

void UJumpAttackProcessor::ConfigureQueries()
{
	EntityQuery.AddRequirement<FTransformFragment>(EMassFragmentAccess::ReadWrite);
	EntityQuery.AddRequirement<FJumpAttackFragment>(EMassFragmentAccess::ReadWrite);
}

void UJumpAttackProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	AActor* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (!Player) return;

	FVector PlayerLocation = Player->GetActorLocation();
	

	EntityQuery.ForEachEntityChunk(EntityManager, Context, [this, PlayerLocation](FMassExecutionContext& Context)
	{
		const TArrayView<FTransformFragment> TransformList = Context.GetMutableFragmentView<FTransformFragment>();
		const TArrayView<FJumpAttackFragment> JumpList = Context.GetMutableFragmentView<FJumpAttackFragment>();
		const float DeltaTime = Context.GetDeltaTimeSeconds();

		bool bAnotherEntityIsJumping = false;
		int EntitiesJumpingNum = 0;

		// First pass: check if someone is already jumping
		for (int32 EntityIndex = 0; EntityIndex < Context.GetNumEntities(); ++EntityIndex)
		{
			FJumpAttackFragment& JumpFragment = JumpList[EntityIndex];
			
			if (JumpList[EntityIndex].bIsJumping)
			{
				EntitiesJumpingNum += 1;
				if(EntitiesJumpingNum >= JumpFragment.FragmentMaxJumpAttacks)
				{
					bAnotherEntityIsJumping = true;
				    break;
				}
			}
		}
		
		for (int32 EntityIndex = 0; EntityIndex < Context.GetNumEntities(); ++EntityIndex)
		{
			FTransform& Transform = TransformList[EntityIndex].GetMutableTransform();
			FJumpAttackFragment& JumpFragment = JumpList[EntityIndex];
			FVector CurrentLocation = Transform.GetLocation();
			float DistanceToPlayer = FVector::Dist2D(CurrentLocation, PlayerLocation);

			JumpFragment.TotalTimeAlive += DeltaTime;

			if (JumpFragment.FragmentJumpDelay <= 0.0f)
			{
				JumpFragment.FragmentJumpDelay = (EntityIndex % Context.GetNumEntities()/2) * 0.5f; 
			}
			
			if (!JumpFragment.bIsJumping && !bAnotherEntityIsJumping &&  DistanceToPlayer < JumpFragment.FragmentJumpAttackRange)
			{
				if (JumpFragment.TotalTimeAlive >= JumpFragment.FragmentJumpDelay)
				{
					// Start Jump
					JumpFragment.bIsJumping = true;
					JumpFragment.ElapsedJumpTime = 0.0f;
					JumpFragment.JumpStartLocation = CurrentLocation;
			
					// Jump target is over the player, some offset forward
					FVector Forward = (PlayerLocation - CurrentLocation).GetSafeNormal();
					FVector JumpTargetLocation = PlayerLocation + Forward * JumpFragment.FragmentJumpDistance;
					JumpTargetLocation.Z = 0.0f;
					JumpFragment.JumpTargetLocation = JumpTargetLocation;

					bAnotherEntityIsJumping = true;
				}
				
			}
			if (JumpFragment.bIsJumping)
			{
				JumpFragment.ElapsedJumpTime += DeltaTime;
				float Alpha = JumpFragment.ElapsedJumpTime / JumpFragment.FragmentJumpDuration;
				Alpha = FMath::Clamp(Alpha, 0.0f, 1.0f);
				FVector Horizontal = FMath::Lerp(JumpFragment.JumpStartLocation, JumpFragment.JumpTargetLocation, Alpha);
				float Height = FMath::Sin(Alpha * PI) * JumpFragment.FragmentJumpHeight;
				FVector NewLocation = Horizontal;
				NewLocation.Z += Height;
				Transform.SetLocation(NewLocation);
				// Rotation (face direction)
				FVector Dir = (JumpFragment.JumpTargetLocation - JumpFragment.JumpStartLocation).GetSafeNormal();
				FRotator LookRot = Dir.Rotation();
				LookRot.Roll = 0.0f;
				LookRot.Pitch = 0.0f;
				Transform.SetRotation(FQuat(LookRot));
				if (Alpha >= 1.0f)
				{
					// Jump done
					JumpFragment.bIsJumping = false;
					JumpFragment.TotalTimeAlive = 0.0f;
				}
			}
		}
		
		
	});
}
