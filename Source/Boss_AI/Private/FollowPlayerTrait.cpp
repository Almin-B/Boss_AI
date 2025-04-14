// Fill out your copyright notice in the Description page of Project Settings.


#include "FollowPlayerTrait.h"
#include "MassEntityTemplateRegistry.h"
#include "Engine/World.h"


void UFollowPlayerTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const
{
	BuildContext.AddFragment_GetRef<FFollowPlayerFragment>().FragmentFollowDistance = FollowDistance;
	BuildContext.AddFragment_GetRef<FFollowPlayerFragment>().FragmentAvoidDistance = AvoidDistance;
	BuildContext.AddFragment_GetRef<FFollowPlayerFragment>().FragmentAvoidPower = AvoidPower;
	BuildContext.AddFragment_GetRef<FFollowPlayerFragment>().FragmentFollowThreshhold = FollowThreshhold;
	BuildContext.AddFragment_GetRef<FFollowPlayerFragment>().FragmentMovementInterpSpeed = MovementInterpSpeed;
	BuildContext.AddFragment_GetRef<FFollowPlayerFragment>().FragmentRotationInterpSpeed = RotationInterpSpeed;
}
