// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PatrolPath.h"
#include "Animation/AnimMontage.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Components/TimelineComponent.h"


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
	Thrust  UMETA(DisplayName = "Thrust"),
	Idle    UMETA(DisplayName = "Idle"),
	Walk_Back    UMETA(DisplayName = "Walk")
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

	//Rootmotion Movement
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BaseEnemy|Movement")
	bool bIsRootmotionEnabled = false;
	UPROPERTY(BlueprintReadOnly, Category = "BaseEnemy|Movement|Rootmotion")
	float CurrentRootmotionAlpha;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BaseEnemy|Movement|Rootmotion")
	float RootmotionUpdateSpeed = 1.2f;
	UFUNCTION(BlueprintCallable)
	void ChangeRootmotionState(EMovemntState NewMovementState);
	
	void UpdateRootmotionAlpha();
	FTimerHandle RootmotionUpdateTimeline;
	
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BaseEnemy|Movement|Rootmotion")
	TMap<EMovemntState, float> MappedRootmotionData;
	
	

	//Base Movement
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BaseEnemy|Movement|BaseMovement")
	float WalkSpeed = 80;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BaseEnemy|Movement|BaseMovement")
	float RunSpeed = 190;

	//Advanced Movement
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BaseEnemy|Movement|AdvanceMovement")
	float StraveSpeed = 80;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BaseEnemy|Movement|AdvanceMovement")
	float ThrustSpeed = 400;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BaseEnemy|Movement|AdvanceMovement")
	float ThrustDistance = 800;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BaseEnemy|Movement|AdvanceMovement")
	float DodgeSpeed = 300;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BaseEnemy|Movement|AdvanceMovement")
	float RotationRate = 360;
	UPROPERTY(BlueprintReadWrite, Category = "BaseEnemy|AI")
	bool bIsDead;

	//Turning Around

	UPROPERTY(BlueprintReadWrite, Category = "BaseEnemy|Movement|AdvanceMovement|Turn")
	bool bIsTurning = false;

	UFUNCTION(BlueprintCallable, Category = "BaseEnemy|Movement|AdvanceMovement|Turn")
	void TurnAround();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BaseEnemy|Movement|AdvanceMovement|Turn")
	float TurnTimelinePlayrate = 1.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BaseEnemy|Movement|AdvanceMovement|Turn")
	UAnimMontage* TurnMontage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BaseEnemy|Movement|AdvanceMovement|Turn")
	UCurveFloat* TurnCurve;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BaseEnemy|Movement|AdvanceMovement|Turn")
	TEnumAsByte<ETimelineDirection::Type> TurnTimelineDirection;

	UFUNCTION()
	void TurnTimelineCallback(float val);
	UFUNCTION()
	void TurnEndCallback();

	void InitTurntimeline();

	UPROPERTY()
	UTimelineComponent* TurnTimeline;
	
	FRotator TurnRotation;
	float StartRotationZ;
	float EndRotationZ;



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
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void ActivateEnemy();

	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool IsLookingAt(FVector TargetLocation, float SightAngle);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

};
