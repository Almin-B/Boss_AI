// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "LanceFighter.h"

#include "DetectPlayerAttack.generated.h"

/**
 * 
 */
UCLASS()
class BOSS_AI_API UDetectPlayerAttack : public UBTService
{
	GENERATED_BODY()

	UDetectPlayerAttack();
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector IsDefense;
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector IsBlocking;
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector Distance;
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector IsFaceingPlayer;
	UPROPERTY(EditAnywhere, Category = Blackboard)
	float MinDistanceToTarget = 500;
};
