// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FollowWalkingPathComponent.h"
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
	// Sets default values for this character's properties
	APlayer_2D();

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UFollowWalkingPathComponent* FollowWalkingPath;

	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	UInventoryComponent* InventoryComp;

	// Player Movement
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
	bool CanTurn();
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Player|Movement|Turn")
	float TurnRate = 1.0f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Player|Movement|Turn")
	UAnimSequenceBase* TurnAnimation;
	
	float TurnDuration;
	FTimerHandle TurnTimerHandle;

	void OnTurnEnd();

	void InitMovementNotifys();

	//Roll
	UPROPERTY(EditDefaultsOnly,Category="Player|Movement|Roll")
	float RollSpeed = 1;
	UPROPERTY(EditDefaultsOnly,Category="Player|Movement|Roll")
	UAnimMontage* RollMontage;
	
	bool bIsRolling;
	UFUNCTION(BlueprintCallable)
	void Roll();

	bool CanRoll();
	
	void OnRollEnd();

	//Player Combat
	UPROPERTY(BlueprintReadWrite)
	AEnemy_Base* Boss_Ref;

	//HitBox
	EPlayerAttackType CurrentPlayerAttack;
	void OnSpawnHitbox();
	void InitHitboxNotify();

	UPROPERTY(EditDefaultsOnly)
	USphereComponent* HitBoxSpawnPoint;
	
	//Light Attack
	bool bIsInLightAttack;

	void LightAttack_Implementation() override;
	void InitLightAttackNotify();
	void OnLightAttackEnd();
	
	//Heavy Attack
	UPROPERTY(EditDefaultsOnly,Category="Player|Combat|HeavyAttack")
	UAnimMontage* HeavyAttack_StrikeUp_Montage;
	UPROPERTY(EditDefaultsOnly,Category="Player|Combat|HeavyAttack")
	UAnimMontage* HeavyAttack_FollowUp_Montage;
	UPROPERTY(EditDefaultsOnly,Category="Player|Combat|Special")
	UAnimMontage* SpecialAttack_Montage;

	bool bIsInHeavyAttack;
	int HeavyAttackComboCount = 0;
	
	void HeavyAttackFollowup();
	void HeavyAttack_Implementation() override;
	void InitHeavyAttackNotify();
	void OnHeavyAttackEnd();

	//Special Attack

	UFUNCTION(BlueprintCallable)
	void SpecialAttack();
	void OnSpecialAttackEnd();
	void InitSpecialAttackNotify();
	bool bIsInSpecialAttack;

	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
