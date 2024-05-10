// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy_Base.h"
#include "Components/TimelineComponent.h"
#include "Curves/CurveFloat.h"
#include "Raccoon.generated.h"

/**
 * 
 */

UCLASS()
class BOSS_AI_API ARaccoon : public AEnemy_Base
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Raccoon|RaccoonAttacks|ArenaDash")
	void ArenaDash();
	UFUNCTION()
	void ArenaDashProgress(float Value);
	UPROPERTY(EditDefaultsOnly, Category = "Raccoon|RaccoonAttacks|ArenaDash")
	UCurveFloat* DashAlpha;
	UPROPERTY(EditDefaultsOnly, Category = "Raccoon|RaccoonAttacks|ArenaDash")
	UCurveFloat* DashAlphaZ;
	UPROPERTY(EditDefaultsOnly, Category = "Raccoon|RaccoonAttacks|ArenaDash")
	float DashSpeed = 1;

	float FlyHeight;
	UPROPERTY(EditDefaultsOnly, Category = "Raccoon|RaccoonAttacks|ArenaDash")
	float DashHeightOffset = 10;
	UPROPERTY(EditDefaultsOnly, Category = "Raccoon|RaccoonAttacks|ArenaDash")
	float ArenaWallOffset = 150;
	UPROPERTY(EditDefaultsOnly, Category = "Raccoon|RaccoonAttacks|ArenaDash")
	bool bShowDashDebug = false;
	UPROPERTY(BlueprintReadWrite, Category = "Raccoon|RaccoonAttacks|ArenaDash|Animation")
	float FlyAnimSpeed = 1;
	UPROPERTY(EditDefaultsOnly, Category = "Raccoon|RaccoonAttacks|ArenaDash|Animation")
	float MaxDashAnimSpeed = 2;
	UPROPERTY(BlueprintReadWrite, Category = "Raccoon|RaccoonAttacks|ArenaDash|Animation")
	float DashAnimAlpha = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Raccoon|RaccoonAttacks|ArenaDash|Animation")
	UAnimMontage* TransitMontage;

	UFUNCTION(BlueprintCallable, Category = "Raccoon")
	void AktivateFlyState();
	UPROPERTY(BlueprintReadWrite, Category = "Raccoon")
	bool bIsFlyState = false;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Raccoon")
	void TransitToFlyState();


protected:

	FTimeline DashTimeline;
	UPROPERTY()
	FVector DashStart;
	UPROPERTY()
	FVector DashEnd;

	void InitArenaDashTimeline();
	
	void InitFlyingPhase();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
