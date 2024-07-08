// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "HeavyAttackFollowUpNotify.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnNotifiedSignature)
/**
 * 
 */
UCLASS()
class BOSS_AI_API UHeavyAttackFollowUpNotify : public UAnimNotify
{
	GENERATED_BODY()

public:

	FOnNotifiedSignature OnNotified;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
