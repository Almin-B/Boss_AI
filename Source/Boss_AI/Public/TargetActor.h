// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetActor.generated.h"

// Event dispatcher to notify listeners when the boolean changes
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBooleanChanged, bool, NewValue);

UCLASS()
class BOSS_AI_API ATargetActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATargetActor();

	// Replicated boolean with notification when changed
	UPROPERTY(ReplicatedUsing= OnRep_MyBool,BlueprintReadOnly)
	bool MyBool = false;

	// Event dispatcher to broadcast changes
	UPROPERTY(BlueprintAssignable)
	FOnBooleanChanged OnBooleanChanged;

	//Setter Function to change the value and trigger replication
	UFUNCTION(BlueprintCallable)
	void SetMyBool(bool NewBool);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
private:
	// Called on clients when the replicated variable changes
	UFUNCTION()
	void OnRep_MyBool();

};
