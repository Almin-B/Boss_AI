// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "CharacterWalkingPath.generated.h"

UCLASS()
class BOSS_AI_API ACharacterWalkingPath : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACharacterWalkingPath();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(MakeEditWidget="true", AllowPrivateAccess="true"), Category="WalkingPath")
	TArray<FVector> CheckPoints;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="WalkingPath")
	bool bIsLoopedPath = false;

	UPROPERTY(BlueprintReadWrite)
	USplineComponent* WalkingPathSpline;
	
	UFUNCTION(BlueprintCallable)
	void CreateWalkingPathSpline();
	


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
