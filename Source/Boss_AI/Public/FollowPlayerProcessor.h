// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MassProcessor.h"
#include "FollowPlayerProcessor.generated.h"

/**
 * 
 */
UCLASS()
class BOSS_AI_API UFollowPlayerProcessor : public UMassProcessor
{
	GENERATED_BODY()

	FMassEntityQuery EntityQuery;

public:
	UFollowPlayerProcessor();
	

	virtual void ConfigureQueries() override;
	virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;
	
	
};
