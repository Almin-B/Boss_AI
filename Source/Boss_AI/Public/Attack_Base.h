// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Attack_Base.generated.h"


/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class BOSS_AI_API UAttack_Base : public UObject
{
	GENERATED_BODY()
public:
	UAttack_Base();
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void AttackExecute();
	
	virtual void AttackExecute_Implementation();

	void AttackEnd();
	
	UFUNCTION(BlueprintCallable)
	void InterruptAttack();

	UPROPERTY(BlueprintReadWrite)
	ACharacter* Owner;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	bool bCanInterruptAttack = false;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UAnimMontage* AttackMontage;

	//Hitbox
	void OnSpawnHitbox();
	void InitHitboxNotify();

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	FVector HitboxSize;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	float Damage;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	float HitboxLifeTime;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	bool bShowDebug;
};
