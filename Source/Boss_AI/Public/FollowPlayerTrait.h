// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MassEntityTraitBase.h"
#include "MassEntityTypes.h"
#include "FollowPlayerTrait.generated.h"

USTRUCT(BlueprintType)
struct FFollowPlayerFragment : public FMassFragment
{
	GENERATED_BODY()

	UPROPERTY()
	FVector TargetLocation;
	UPROPERTY()
	FRotator TargetRotation;
	UPROPERTY()
	bool bIsMoving = false;
	UPROPERTY(EditAnywhere)
	float FragmentFollowDistance = 100.0f;
	UPROPERTY(EditAnywhere)
	float FragmentAvoidDistance = 500.0f;
	UPROPERTY(EditAnywhere)
	float FragmentAvoidPower = 1000.0f;
	UPROPERTY(EditAnywhere)
	float FragmentFollowThreshhold = 30.0f;
	UPROPERTY(EditAnywhere)
	float FragmentMovementInterpSpeed = 2.0f;
	UPROPERTY(EditAnywhere)
	float FragmentRotationInterpSpeed = 5.0f;
};

UCLASS()
class BOSS_AI_API UFollowPlayerTrait : public UMassEntityTraitBase
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere)
	float FollowDistance = 200.0f;
	UPROPERTY(EditAnywhere)
	float AvoidDistance = 500.0f;
	UPROPERTY(EditAnywhere)
	float AvoidPower = 1000.0f;
	UPROPERTY(EditAnywhere)
	float FollowThreshhold = 30.0f;
	UPROPERTY(EditAnywhere)
	float MovementInterpSpeed = 2.0f;
	UPROPERTY(EditAnywhere)
	float RotationInterpSpeed = 5.0f;
	
	virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;
	
};
