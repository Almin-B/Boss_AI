// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MassEntityTraitBase.h"
#include "MassEntityTypes.h"
#include "JumpAttackTrait.generated.h"

USTRUCT()
struct FJumpAttackFragment : public FMassFragment
{
	GENERATED_BODY()

	UPROPERTY()
	float FragmentJumpAttackRange = 200.0f;
	UPROPERTY()
	float FragmentJumpDistance = 330.0f;
	UPROPERTY()
	float FragmentJumpHeight = 70.0f;
	UPROPERTY()
	float FragmentJumpDuration = 0.89f;
	UPROPERTY()
	bool bIsJumping = false;
	UPROPERTY()
	int FragmentMaxJumpAttacks = 3;
	UPROPERTY()
	float FragmentJumpDelay = 0.0f;
	UPROPERTY()
	float ElapsedJumpTime = 0.0f;
	UPROPERTY()
	float TotalTimeAlive = 0.0f;
	UPROPERTY()
	FVector JumpStartLocation;
	UPROPERTY()
	FVector JumpTargetLocation;
};
UCLASS()
class BOSS_AI_API UJumpAttackTrait : public UMassEntityTraitBase
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere)
	float JumpAttackRange = 200.0f;
	UPROPERTY(EditAnywhere)
	float JumpDistance = 200.0f;
	UPROPERTY(EditAnywhere)
	float JumpHeight = 70.0f;
	UPROPERTY(EditAnywhere)
	float JumpDuration = 0.89f;
	UPROPERTY(EditAnywhere)
	int MaxJumpAttacks = 3;
	
	virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;
};
