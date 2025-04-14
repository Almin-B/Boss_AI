// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MassEntityTypes.h" 
#include "MassProcessor.h"
#include "SimpleRandomMovementProcessor.generated.h"

/**
 * 
 */
UCLASS()
class BOSS_AI_API USimpleRandomMovementProcessor : public UMassProcessor
{
	GENERATED_BODY()
public:
	USimpleRandomMovementProcessor();
protected:
	virtual void ConfigureQueries() override;
	virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;
	
private:
	FMassEntityQuery EntityQuery;
};
