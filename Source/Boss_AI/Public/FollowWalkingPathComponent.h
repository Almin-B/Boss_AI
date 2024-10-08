// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterWalkingPath.h"
#include "Components/ActorComponent.h"
#include "Components/SplineComponent.h"
#include "FollowWalkingPathComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOSS_AI_API UFollowWalkingPathComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFollowWalkingPathComponent();
	
	void UpdateOwnerRotation();
	UPROPERTY(BlueprintReadWrite)
	bool bIsUpdateActive = true;
	UPROPERTY(EditDefaultsOnly)
	bool bSnapToPath;
	UPROPERTY(EditDefaultsOnly)
	float LineOffset = 0.0f; 

	UFUNCTION(BlueprintCallable)
	void SetIsUpdateActive(bool isActive);
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	ACharacterWalkingPath* WalkingPathReference;
	
	APawn* Owner;
	FRotator GetSplineRotation();
	FVector GetOwnerLocation();

	void SnapOwnerToPath();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
