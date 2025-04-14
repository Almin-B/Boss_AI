// Fill out your copyright notice in the Description page of Project Settings.


#include "EntityApperance.h"

#include "FollowPlayerTrait.h"
#include "JumpAttackTrait.h"
#include "MassCommonFragments.h"
#include "MassEntityTemplateRegistry.h"
#include "MassRepresentationFragments.h"
#include "MassRepresentationTypes.h"

void UEntityApperance::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const
{
	
	BuildContext.AddFragment_GetRef<FEntityApperanceFragment>().Mesh = VisualMesh;
	BuildContext.AddFragment_GetRef<FEntityApperanceFragment>().FragmentVertexAnmimationMap = VertexAnmimationMap;
	BuildContext.AddFragment_GetRef<FEntityApperanceFragment>().FragmentEntitySize = EntitySize;
	BuildContext.AddFragment<FTransformFragment>();
	BuildContext.AddFragment<FFollowPlayerFragment>();
	BuildContext.AddFragment<FJumpAttackFragment>();
}
