// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player_Base.h"
#include "Player_Guts.generated.h"

/**
 * 
 */
UCLASS()
class BOSS_AI_API APlayer_Guts : public APlayer_Base
{
	GENERATED_BODY()

public:

	APlayer_Guts();

	UPROPERTY(BlueprintReadWrite)
	bool bIsInLightAttack;
	UPROPERTY(BlueprintReadWrite)
	bool bIsInHeavyAttack;
	UPROPERTY(BlueprintReadWrite)
	bool bIsInSpecialAttack;

	UPROPERTY(EditDefaultsOnly)
	USphereComponent* HitBoxSpawnPoint;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
