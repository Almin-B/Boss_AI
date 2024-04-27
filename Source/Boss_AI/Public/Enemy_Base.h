// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PatrolPath.h"
#include "Animation/AnimMontage.h"
#include "BehaviorTree/BehaviorTree.h"


#include "Enemy_Base.generated.h"

UENUM(BlueprintType)
enum class EAttackType : uint8
{
	Attack_1 UMETA(DisplayName = "Attack 1"),
	Attack_2 UMETA(DisplayName = "Attack 2"),
	Attack_3 UMETA(DisplayName = "Attack 3"),
	Attack_4 UMETA(DisplayName = "Attack 4"),
	Attack_Thrust UMETA(DisplayName = "Attack Thrust")
};

UENUM(BlueprintType)
enum class EMovemntState : uint8
{
	Walk    UMETA(DisplayName = "Walk"),
	Run     UMETA(DisplayName = "Run"),
	Strave  UMETA(DisplayName = "Strave"),
	Thrust  UMETA(DisplayName = "Thrust")
};

UENUM(BlueprintType)
enum class EDodgeDirection : uint8
{
	Left UMETA(DisplayName = "Left"),
	Right UMETA(DisplayName = "Right"),
	Back UMETA(DisplayName = "Back")
};


UCLASS()
class BOSS_AI_API AEnemy_Base : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy_Base();


	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "BaseEnemy|AI")
	APatrolPath* PatrolPath;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BaseEnemy|Movement")
	float WalkSpeed = 80;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BaseEnemy|Movement")
	float RunSpeed = 190;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BaseEnemy|Movement")
	float StraveSpeed = 80;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BaseEnemy|Movement")
	float ThrustSpeed = 400;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BaseEnemy|Movement")
	float ThrustDistance = 800;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BaseEnemy|Movement")
	float DodgeSpeed = 300;
	UPROPERTY(BlueprintReadWrite, Category = "BaseEnemy|AI")
	bool bIsDead;


	UPROPERTY(BlueprintReadWrite, Category = "BaseEnemy|Movement")
	EMovemntState CurrentMovemntState = EMovemntState::Walk;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BaseEnemy|AI")
	UBehaviorTree* EnemyBehaviorTree;

	void UpdateMovementState();
	void Dodge(EDodgeDirection DodgeDirection);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void TakeHit(float Damage);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void BreakGurad();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Death();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BaseEnemy|Defense")
	bool bIsBlocking;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BaseEnemy|Defense")
	float BlockAlpha;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BaseEnemy|Defense")
	float Health = 100;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BaseEnemy|Defense")
	float MaxHealth = 100;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BaseEnemy|Defense")
	float Guard = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BaseEnemy|Defense")
	float GuardEfficiency = 50;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BaseEnemy|Defense")
	bool bIsGuardBroken;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BaseEnemy|Defense")
	float KnockBackPower = 1500;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BaseEnemy|Defense")
	float GuardBreakDamage = 25;
	UPROPERTY(BlueprintReadWrite, Category = "BaseEnemy|Defense")
	int BlockedHits;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BaseEnemy|Defense")
	bool bIsDecreasingStarted;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BaseEnemy|Defense")
	float GuardDecreaseAmount;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BaseEnemy|Defense")
	float GuardDecreaseDelay;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BaseEnemy|Defense")
	float GuardDecreaseInterval;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
