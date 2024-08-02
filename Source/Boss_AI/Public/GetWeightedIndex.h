// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "GetWeightedIndex.generated.h"

/**
 *
 *
 */

USTRUCT(BlueprintType)
struct FWeightedInex
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int Index;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Weight;
};



UCLASS()
class BOSS_AI_API UGetWeightedIndex : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, Category = Blackboard)
	TArray<FWeightedInex> IndexArray;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector Index;

	explicit UGetWeightedIndex(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	int ChoosenIndex; 
	int ChooseIndex();
};

