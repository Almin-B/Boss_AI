// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "LanceFighter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "FollowUpDefenseAttack.generated.h"

/**
 * 
 */
UCLASS()
class BOSS_AI_API UFollowUpDefenseAttack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere)
	float FollowUpProbability = 10.0f;


	explicit UFollowUpDefenseAttack(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
