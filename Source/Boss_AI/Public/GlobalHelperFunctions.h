// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"


#include "GlobalHelperFunctions.generated.h"

/**
 * 
 */
UCLASS()
class BOSS_AI_API UGlobalHelperFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UGlobalHelperFunctions(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "HitBox")
	static void SpawnHitBox(float Damage, FVector HitBoxSize,FVector Location,FRotator Rotation, float LifeTime, bool ShowDebug, bool IsFromEnemy, AActor* ParentActor, AActor* Owner);
	
};
