// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "Enemy_Base.h"
#include "Kismet/GameplayStatics.h"

#include "Enemy_Controller.generated.h"

/**
 * 
 */
UCLASS()
class BOSS_AI_API AEnemy_Controller : public AAIController
{
	GENERATED_BODY()
	
public:
	explicit AEnemy_Controller(FObjectInitializer const& ObjectInitializer);

	UFUNCTION(BlueprintImplementableEvent)
	void NearTarget();

	UPROPERTY(EditDefaultsOnly, Category = "SenseSettings")
	float SightRadius = 1500.0f;
	UPROPERTY(EditDefaultsOnly, Category = "SenseSettings")
	float PeripheralVisionAngleDegrees = 90.f;

protected:
	virtual void OnPossess(APawn* InPawn) override;
private:
	class UAISenseConfig_Sight* SightConfig;

	void SetupPreceptionSystem();

	UFUNCTION()
	void OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus);

};
