// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Enemy_Base.h"
#include "LanceFighter.h"

#include "AbortCurrentAttackMontage.generated.h"

/**
 * 
 */
UCLASS()
class BOSS_AI_API UAbortCurrentAttackMontage : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:

	explicit UAbortCurrentAttackMontage(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
