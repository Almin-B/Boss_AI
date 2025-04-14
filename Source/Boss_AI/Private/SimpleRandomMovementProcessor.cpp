// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleRandomMovementProcessor.h"

#include "AIController.h"
#include "MassCommonFragments.h"
#include "MassEntityTemplateRegistry.h"
#include "MassRepresentationFragments.h"
#include "SimpleRadnomMovementTrait.h"

USimpleRandomMovementProcessor::USimpleRandomMovementProcessor():EntityQuery(*this)
{
	bAutoRegisterWithProcessingPhases = true;
	ExecutionFlags = (int32)EProcessorExecutionFlags::All;
	ExecutionOrder.ExecuteBefore.Add(UE::Mass::ProcessorGroupNames::Avoidance);
}

void USimpleRandomMovementProcessor::ConfigureQueries()
{
	EntityQuery.AddRequirement<FTransformFragment>(EMassFragmentAccess::ReadWrite);
	EntityQuery.AddRequirement<FSimpleMovementFragment>(EMassFragmentAccess::ReadWrite);
}

void USimpleRandomMovementProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	EntityQuery.ForEachEntityChunk(EntityManager, Context, ([this](FMassExecutionContext& Context)
	{
		const TArrayView<FTransformFragment> TransformList = Context.GetMutableFragmentView<FTransformFragment>();
		const TArrayView<FSimpleMovementFragment> SimpleMovementsList = Context.GetMutableFragmentView<FSimpleMovementFragment>();
		const float WorldDeltaTime = Context.GetDeltaTimeSeconds();

		for(int32 EntityIndex = 0; EntityIndex < Context.GetNumEntities(); ++EntityIndex)
		{
			FTransform& Transform = TransformList[EntityIndex].GetMutableTransform();
			FVector& MoveTarget = SimpleMovementsList[EntityIndex].Target;

			FVector CurrentLocation = Transform.GetLocation();
			FVector TargetVector = MoveTarget - CurrentLocation;

			if(TargetVector.Size() <= 20.0f)
			{
				MoveTarget = FVector(FMath::RandRange(-1.0f, 1.0f) * 1000.0f, FMath::RandRange(-1.0f,1.0f) * 1000.0f,CurrentLocation.Z);
			}
			else
			{
				Transform.SetLocation(CurrentLocation + TargetVector.GetSafeNormal() * 400.0f * WorldDeltaTime);
			}
		}
	}));
}
