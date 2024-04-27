// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

#include "GetPlayerLocation.generated.h"

/**
 * 
 */
UCLASS()
class BOSS_AI_API UGetPlayerLocation : public UBTService
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector TargetLocation;

	UGetPlayerLocation();
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
