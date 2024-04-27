// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Enemy_Base.h"
#include "Math/UnrealMathUtility.h"
#include "NavigationSystem.h"
#include "NavigationData.h"

#include "FindReachableStraveLocation.generated.h"

/**
 * 
 */
UCLASS()
class BOSS_AI_API UFindReachableStraveLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinStraveDistance = 350;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxStraveDistance = 450;

	explicit UFindReachableStraveLocation(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
