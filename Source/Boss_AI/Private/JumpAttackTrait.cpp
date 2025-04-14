// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpAttackTrait.h"
#include "MassEntityTypes.h"
#include "MassEntityTemplateRegistry.h"

void UJumpAttackTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const
{
	BuildContext.AddFragment_GetRef<FJumpAttackFragment>().FragmentJumpAttackRange = JumpAttackRange;
	BuildContext.AddFragment_GetRef<FJumpAttackFragment>().FragmentJumpDistance = JumpDistance;
	BuildContext.AddFragment_GetRef<FJumpAttackFragment>().FragmentJumpDuration = JumpDuration;
	BuildContext.AddFragment_GetRef<FJumpAttackFragment>().FragmentJumpHeight = JumpHeight;
	BuildContext.AddFragment_GetRef<FJumpAttackFragment>().FragmentMaxJumpAttacks = MaxJumpAttacks;
}
