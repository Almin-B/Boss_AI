// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "EventTrigger_Base.generated.h"

UCLASS()
class BOSS_AI_API AEventTrigger_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEventTrigger_Base();

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* TriggerBox;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="EventTrigger")
	FVector TriggerBoxSize;

	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void OnEventExecute();
	virtual void OnEventExecute_Implementation();
	UPROPERTY(BlueprintReadWrite)
	bool bIsEventExecuted = false;

	UFUNCTION(BlueprintCallable)
	void UpdateTriggerBoxSize(FVector Size);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
