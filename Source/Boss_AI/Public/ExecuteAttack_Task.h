// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "ExecuteAttack_Task.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class BOSS_AI_API UExecuteAttack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName AttackName;
	
	explicit UExecuteAttack(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
