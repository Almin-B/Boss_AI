// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "Projectile_Base.generated.h"

UCLASS()
class BOSS_AI_API AProjectile_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile_Base();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float ProjectileSpeed;

	void SetupProjectileMovement();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	
	class UProjectileMovementComponent* ProjectileComponent;

};
