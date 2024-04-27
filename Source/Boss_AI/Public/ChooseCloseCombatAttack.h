// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "LanceFighter.h"

#include "ChooseCloseCombatAttack.generated.h"

/**
 * 
 */
UCLASS()
class BOSS_AI_API UChooseCloseCombatAttack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:

	explicit UChooseCloseCombatAttack(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
