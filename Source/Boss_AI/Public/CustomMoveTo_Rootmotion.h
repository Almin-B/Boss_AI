// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "CustomMoveTo_Rootmotion.generated.h"

/**
 * 
 */
UCLASS()
class BOSS_AI_API UCustomMoveTo_Rootmotion : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector DistanceToTarget;

	
	explicit UCustomMoveTo_Rootmotion(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
