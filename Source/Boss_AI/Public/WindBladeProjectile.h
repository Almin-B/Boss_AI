// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile_Base.h"
#include "Components/StaticMeshComponent.h"

#include "WindBladeProjectile.generated.h"

/**
 * 
 */
UCLASS()
class BOSS_AI_API AWindBladeProjectile : public AProjectile_Base
{
	GENERATED_BODY()

public:
	AWindBladeProjectile();
	
	UPROPERTY(Instanced, EditInstanceOnly)
	class UStaticMeshComponent* WindBladeMesh;


	void SpawnWindBladeVFX();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
