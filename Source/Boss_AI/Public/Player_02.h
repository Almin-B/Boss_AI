// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player_Base.h"
#include "Player_Guts.h"
#include "Player_02.generated.h"

/**
 * 
 */
UCLASS()
class BOSS_AI_API APlayer_Guts_3D : public APlayer_Guts
{
	GENERATED_BODY()

	APlayer_Guts_3D();

public:
	
	UFUNCTION(BlueprintCallable)
	void AddRootmotionMovementInput(float ForwardAxisValue, float RightAxisValue,float MovementThreshold);
	UFUNCTION(BlueprintCallable)
	void OrientRotationToRootmotion(float ForwardAxisValue, float RightAxisValue,float MovementThreshold);
	
	FRotator NewOrientRotation;
	
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	UInventoryComponent* InventoryComp;

	UPROPERTY(BlueprintReadWrite,Category="Player|Movement")
	float MoveRightAxisValue;
	UPROPERTY(BlueprintReadWrite,Category="Player|Movement")
	float MoveForwardAxisValue;
	UPROPERTY(BlueprintReadWrite,Category="Player|Movement")
	bool bIsSprinting;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
