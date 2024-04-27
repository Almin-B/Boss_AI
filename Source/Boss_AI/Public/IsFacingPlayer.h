// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

#include "IsFacingPlayer.generated.h"

/**
 * 
 */
UCLASS()
class BOSS_AI_API UIsFacingPlayer : public UBTService
{
	GENERATED_BODY()


	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector IsFacing;
	UPROPERTY(EditAnywhere, Category = Blackboard)
	float ViewAngle = 45.0f;

	UIsFacingPlayer();
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
