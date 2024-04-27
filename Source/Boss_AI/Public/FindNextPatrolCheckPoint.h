// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "Enemy_Base.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "FindNextPatrolCheckPoint.generated.h"

/**
 * 
 */
UCLASS()
class BOSS_AI_API UFindNextPatrolCheckPoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	

public:
	explicit UFindNextPatrolCheckPoint(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


};
