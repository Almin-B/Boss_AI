// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Turn_Rootmotion.generated.h"

/**
 * 
 */
UCLASS()
class BOSS_AI_API UTurn_Rootmotion : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:


	explicit UTurn_Rootmotion(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
