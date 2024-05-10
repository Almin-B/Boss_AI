// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "IsFacingTarget.generated.h"

/**
 * 
 */
UCLASS()
class BOSS_AI_API UIsFacingTarget : public UBTService
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector IsFacing;
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector TargetLocation;
	UPROPERTY(EditAnywhere, Category = Blackboard)
	float ViewAngle = 45.0f;

	UIsFacingTarget();
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
