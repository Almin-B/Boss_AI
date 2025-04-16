// Fill out your copyright notice in the Description page of Project Settings.


#include "EntityApperanceProcessor.h"

#include "EntityApperance.h"
#include "FollowPlayerTrait.h"
#include "JumpAttackTrait.h"
#include "MassCommonFragments.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "MassRepresentationFragments.h"
#include "MassEntitySubsystem.h"
#include "MassCommonTypes.h"
#include "MassCommonTypes.h"
#include "MassCommonFragments.h"
#include "MassExecutionContext.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/StaticMeshActor.h"

UEntityApperanceProcessor::UEntityApperanceProcessor():EntityQuery(*this)
{
	ExecutionOrder.ExecuteInGroup = TEXT("Representation");
	ExecutionFlags = (int32)EProcessorExecutionFlags::All;
	bAutoRegisterWithProcessingPhases = true;
	ProcessingPhase = EMassProcessingPhase::PostPhysics;
}

void UEntityApperanceProcessor::ConfigureQueries()
{
	EntityQuery.AddRequirement<FEntityApperanceFragment>(EMassFragmentAccess::ReadWrite);
	EntityQuery.AddRequirement<FTransformFragment>(EMassFragmentAccess::ReadOnly);
	EntityQuery.AddRequirement<FFollowPlayerFragment>(EMassFragmentAccess::ReadOnly);
	EntityQuery.AddRequirement<FJumpAttackFragment>(EMassFragmentAccess::ReadOnly);
}

void UEntityApperanceProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	
	EntityQuery.ForEachEntityChunk(EntityManager, Context, [this](FMassExecutionContext& Context)
	{
		const int32 NumEntities = Context.GetNumEntities();

		const TArrayView<FEntityApperanceFragment> ApperanceList = Context.GetMutableFragmentView<FEntityApperanceFragment>();
		const TArrayView<FTransformFragment> TransformList = Context.GetMutableFragmentView<FTransformFragment>();
		const TArrayView<FFollowPlayerFragment> FollowPlayerList = Context.GetMutableFragmentView<FFollowPlayerFragment>();
		const TArrayView<FJumpAttackFragment> JumpAttackList = Context.GetMutableFragmentView<FJumpAttackFragment>();
		
		UWorld* World = Context.GetWorld();


		
		for (int32 EntityIndex = 0; EntityIndex < NumEntities; ++EntityIndex)
		{
			const FJumpAttackFragment& JumpAttackFragment = JumpAttackList[EntityIndex];
			const FFollowPlayerFragment& FollowPlayerFragment = FollowPlayerList[EntityIndex];
			FEntityApperanceFragment& ApperanceFragment = ApperanceList[EntityIndex];
			const FTransformFragment& TransformFragment = TransformList[EntityIndex];
			const FTransform& EntityTransform = TransformFragment.GetTransform();

			if (!ApperanceFragment.bHasVisual && ApperanceFragment.Mesh && EntityTransform.IsValid())
			{
				FTransform SpawnTransform = TransformFragment.GetTransform();
				UStaticMesh* MeshToUse = ApperanceFragment.Mesh;
				

				// Defer to game thread to spawn the actor
				AsyncTask(ENamedThreads::GameThread, [World, SpawnTransform, MeshToUse,&ApperanceFragment,&FollowPlayerFragment]()
				{
					AStaticMeshActor* ApperanceActor = World->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass(), SpawnTransform);
					
					if (ApperanceActor)
					{
						ApperanceActor->SetMobility(EComponentMobility::Type::Movable);

						UStaticMeshComponent* StaticMeshComp = ApperanceActor->GetStaticMeshComponent();
						StaticMeshComp->SetStaticMesh(MeshToUse);
						StaticMeshComp->SetWorldScale3D(FVector(ApperanceFragment.FragmentEntitySize));
						UMaterialInterface* BaseMaterial = StaticMeshComp->GetMaterial(0);

						if(BaseMaterial)
						{
							UMaterialInstanceDynamic* DynMaterial = UMaterialInstanceDynamic::Create(BaseMaterial, ApperanceActor);
							StaticMeshComp->SetMaterial(0,DynMaterial);
							ApperanceFragment.Material = DynMaterial;
							ApperanceFragment.Material->SetScalarParameterValue(FName("SpeedVariation"), FMath::RandRange(-0.2f,0.2f));
						}
						
						ApperanceFragment.VisualActor = ApperanceActor;
						ApperanceFragment.bHasVisual = true;
						ApperanceFragment.LastKnownLocation = SpawnTransform.GetLocation();
					}
				});
			}
			else if(ApperanceFragment.VisualActor.IsValid())
			{
				// Update actor transform from entity transform on game thread
				AStaticMeshActor* VisualActor = Cast<AStaticMeshActor>(ApperanceFragment.VisualActor.Get());

				if (VisualActor)
				{
					const FVector NewLocation = EntityTransform.GetLocation();
					const FRotator NewRotation = EntityTransform.GetRotation().Rotator();

					UMaterialInstanceDynamic* MaterialToUpdate = ApperanceFragment.Material;
					
					AsyncTask(ENamedThreads::GameThread, [VisualActor, NewLocation, NewRotation,MaterialToUpdate, EntityIndex,&FollowPlayerFragment,&JumpAttackFragment,&ApperanceFragment]()
					{
						VisualActor->SetActorLocationAndRotation(NewLocation, NewRotation);
						VisualActor->SetActorRotation(NewRotation + FRotator(0, -90.0f, 0));

						if (MaterialToUpdate)
						{
							//VertexAnimation Handling
							if(!JumpAttackFragment.bIsJumping)
							{
								if(FollowPlayerFragment.bIsMoving)
								{
									//Set StartFrame and EndFrame to Run
									MaterialToUpdate->SetScalarParameterValue(FName("StartFrame"), ApperanceFragment.FragmentVertexAnmimationMap.Find(EVertexAnimationState::Run)->StartFrame);
									MaterialToUpdate->SetScalarParameterValue(FName("EndFrame"), ApperanceFragment.FragmentVertexAnmimationMap.Find(EVertexAnimationState::Run)->EndFrame);
								}
								else
								{
									//Set StartFrame and EndFrame to Idle
									MaterialToUpdate->SetScalarParameterValue(FName("StartFrame"), ApperanceFragment.FragmentVertexAnmimationMap.Find(EVertexAnimationState::Idle)->StartFrame);
									MaterialToUpdate->SetScalarParameterValue(FName("EndFrame"), ApperanceFragment.FragmentVertexAnmimationMap.Find(EVertexAnimationState::Idle)->EndFrame);
								}
							}
							else
							{
								//Set StartFrame and EndFrame to Jump
								MaterialToUpdate->SetScalarParameterValue(FName("StartFrame"), ApperanceFragment.FragmentVertexAnmimationMap.Find(EVertexAnimationState::Jump)->StartFrame);
								MaterialToUpdate->SetScalarParameterValue(FName("EndFrame"), ApperanceFragment.FragmentVertexAnmimationMap.Find(EVertexAnimationState::Jump)->EndFrame);
							}
						}
						
					});
					ApperanceFragment.LastKnownLocation = NewLocation;
				}
			}
		}
	});
}
