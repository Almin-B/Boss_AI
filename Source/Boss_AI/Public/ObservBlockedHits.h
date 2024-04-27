// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Enemy_Base.h"

#include "ObservBlockedHits.generated.h"

/**
 * 
 */
UCLASS()
class BOSS_AI_API UObservBlockedHits : public UBTService
{
	GENERATED_BODY()

public:

	UObservBlockedHits();
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector BlockedHits;
	
};
