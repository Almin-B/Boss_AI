// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MassEntityTraitBase.h"
#include "MassEntityTypes.h"
#include "SimpleRadnomMovementTrait.generated.h"

USTRUCT()
struct FSimpleMovementFragment : public FMassFragment
{
	GENERATED_BODY()
	FVector Target;
};


UCLASS()
class BOSS_AI_API USimpleRadnomMovementTrait : public UMassEntityTraitBase
{
	GENERATED_BODY()
	
public:
	virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;
};
