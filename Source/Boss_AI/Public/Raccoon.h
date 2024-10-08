// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BossHealthbarComponent.h"
#include "Enemy_Base.h"
#include "Components/TimelineComponent.h"
#include "FollowWalkingPathComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/TargetPoint.h"


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
	UBossHealthbarComponent* BossHealthbar;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UFollowWalkingPathComponent* FollowWalkingPath;

	void TurnAround() override;
	void TurnEndCallback() override;

	UPROPERTY(EditDefaultsOnly,Category="Raccoon")
	UAnimMontage* BossEntranceMontage;
	
	bool bIsInBossentrance = false;
	
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void StartBossEntrance();
	
	virtual void StartBossEntrance_Implementation();
	
	void InitMontagesNotify();
	void OnBossEndtranceEnd();

	virtual void TakeHit_Implementation(float Damage) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Raccoon|Combat|RollAttack")
	ATargetPoint* RollStartPoint;
	
protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
