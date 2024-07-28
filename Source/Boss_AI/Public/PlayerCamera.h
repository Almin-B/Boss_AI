// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player_Base.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerCamera.generated.h"

UCLASS()
class BOSS_AI_API APlayerCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerCamera();

	
	UCameraComponent* PlayerCam;
	USphereComponent* Anchor;
	UPROPERTY(EditDefaultsOnly)
	USpringArmComponent* CameraArm;

	UPROPERTY(EditAnywhere, Category="PlayerCamera|Settings")
	APlayer_Base* PlayerRef;

	UFUNCTION(BlueprintCallable)
	void FocusActor(AActor* ActorToFocus);

	UPROPERTY(EditDefaultsOnly, Category="PlayerCamera|Settings")
	bool ActivateOnBeginPlay = false;
	UPROPERTY(EditDefaultsOnly, Category="PlayerCamera|Settings")
	float CameraDistance = 500.0f;
	UPROPERTY(EditDefaultsOnly, Category="PlayerCamera|Settings")
	float CameraAngle = 45.0f;
	UPROPERTY(EditDefaultsOnly, Category="PlayerCamera|Settings")
	float CameraBlendTime = 2.5f;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category="PlayerCamera|Settings")
	float CameraFollowSpeed = 10;
	UPROPERTY(EditDefaultsOnly, Category="PlayerCamera|Settings")
	float RotationZ;

	void SetupCamera();

	UFUNCTION(BlueprintCallable)
	void SetCameraLag(float LagValue);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
