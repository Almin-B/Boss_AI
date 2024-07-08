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
	float GetCurrentMoveDirectionAlpha();
	UPROPERTY(BlueprintReadWrite,Category="Player|Movement")
	bool bIsTurning = false;
	UPROPERTY(BlueprintReadWrite,Category="Player|Movement")
	bool bIsSprinting;
	UPROPERTY(BlueprintReadWrite,Category="Player|Movement")
	float MoveRightAxisValue;
	UPROPERTY(BlueprintReadWrite,Category="Player|Movement")
	float RootVelocity;

	//Player Combat
	
	UPROPERTY(EditDefaultsOnly,Category="Player|Combat|HeavyAttack")
	UAnimMontage* HeavyAttack_FollowUp_Montage;
	UPROPERTY(EditDefaultsOnly,Category="Player|Combat|Special")
	UAnimMontage* SpecialAttack;

	bool bIsInHeavyAttack;
	
	void HeavyAttackFollowup();
	void HeavyAttack_Implementation() override;
	void InitHeavyAttackNotify();
	void OnHeavyAttackEnd();

	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
