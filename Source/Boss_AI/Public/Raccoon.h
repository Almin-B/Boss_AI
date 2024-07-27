// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy_Base.h"
#include "Components/TimelineComponent.h"
#include "FollowWalkingPathComponent.h"


#include "Raccoon.generated.h"

/**
 * 
 */

UCLASS()
class BOSS_AI_API ARaccoon : public AEnemy_Base
{
	GENERATED_BODY()

public:

	ARaccoon();

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UFollowWalkingPathComponent* FollowWalkingPath;

	void TurnAround() override;
	void TurnEndCallback() override;

	
protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
