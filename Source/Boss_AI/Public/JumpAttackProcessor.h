// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MassProcessor.h"
#include "MassEntityView.h"
#include "JumpAttackProcessor.generated.h"

/**
 * 
 */
UCLASS()
class BOSS_AI_API UJumpAttackProcessor : public UMassProcessor
{
	GENERATED_BODY()

public:
	UJumpAttackProcessor();

protected:
	virtual void ConfigureQueries() override;
	virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;

	FMassEntityQuery EntityQuery;
	
};
