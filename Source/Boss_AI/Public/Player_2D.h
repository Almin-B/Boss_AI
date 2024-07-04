// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player_Base.h"
#include "Player_2D.generated.h"

/**
 * 
 */
UCLASS()
class BOSS_AI_API APlayer_2D : public APlayer_Base
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void DetectMoveDirection(float AxisValue);
	UFUNCTION(BlueprintCallable)
	void Turn();
	float CurrentMoveDirectionAlpha = 1;
	UPROPERTY(BlueprintReadWrite,Category="Player|Movement")
	bool bIsTurning = false;
	UPROPERTY(BlueprintReadWrite,Category="Player|Movement")
	float MoveRightAxisValue;
};
