// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "LanceFighter.h"

#include "GetDistanceTarget.generated.h"

/**
 * 
 */
UCLASS()
class BOSS_AI_API UGetDistanceTarget : public UBTService
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector TargetLocation;
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector Distance;

	UGetDistanceTarget();
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
