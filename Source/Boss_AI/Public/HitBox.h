// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"

#include "HitBox.generated.h"

UCLASS()
class BOSS_AI_API AHitBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHitBox();

	//HitBox Values
	float Damage;
	float LifeTime = 5;
	FVector HitBoxSize = FVector(32,32,32);
	bool bHasHit = false;
	bool bShowHitBoxBounds = true;
	bool bIsEnemy;
	AActor* HitBoxOwner;



	
	UBoxComponent* HitBoxCollsion;

	FTimerHandle DestroyTimer;
	FTimerHandle InitializeTimer;

	void InitializeHitBox();
	void DestroyHitBox();

	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void SpawnHitBoxOverlapCheck();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
