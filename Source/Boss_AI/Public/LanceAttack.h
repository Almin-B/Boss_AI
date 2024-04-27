// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Enemy_Base.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Animation/AnimMontage.h"

#include "LanceAttack.generated.h"

/**
 * 
 */
UCLASS()
class BOSS_AI_API ULanceAttack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAttackType AttackType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThrustAttack")
	bool UseDash = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThrustAttack")
	float DashPower = 8000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThrustAttack")
	float MinDistacne = 600;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ThrustAttack")
	float MaxDistacne = 800;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GeneralAttackSettings")
	float AttackSpeed;

	bool ExecuteThrustAttack(UBehaviorTreeComponent& OwnerComp);
	bool ExecuteWindProjectileAttack(UBehaviorTreeComponent& OwnerComp);
	bool ExecuteCloseCombatAttack(UBehaviorTreeComponent& OwnerComp, EAttackType Attack);




	explicit ULanceAttack(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	
};
