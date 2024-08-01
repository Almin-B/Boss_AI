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

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void AttackEnd();

	virtual void AttackEnd_Implementation();
	
	UFUNCTION(BlueprintCallable)
	void InterruptAttack();

	UPROPERTY(BlueprintReadWrite)
	ACharacter* Owner;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	bool bCanInterruptAttack = false;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UAnimMontage* AttackMontage;

	//Hitbox
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void OnSpawnHitbox();

	virtual void OnSpawnHitbox_Implementation();

	UPROPERTY(BlueprintReadWrite)
	FVector HitBoxSpawnLocation;

	bool bIsSpawned = false;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	FVector HitboxSize;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	float Damage;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	float HitboxLifeTime;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	bool bShowDebug;
};
