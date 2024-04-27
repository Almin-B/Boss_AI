// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Enemy_Base.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "ResetBlockedHitsCounter.generated.h"

/**
 * 
 */
UCLASS()
class BOSS_AI_API UResetBlockedHitsCounter : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:

	explicit UResetBlockedHitsCounter(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
