// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EntityApperance.h"
#include "MassProcessor.h"
#include "EntityApperanceProcessor.generated.h"

/**
 * 
 */
UCLASS()
class BOSS_AI_API UEntityApperanceProcessor : public UMassProcessor
{
	GENERATED_BODY()

public:
	UEntityApperanceProcessor();

	virtual void ConfigureQueries() override;
	virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;

	FMassEntityQuery EntityQuery;
};
