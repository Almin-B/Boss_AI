// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AsyncBoolListener.generated.h"

// Delegate used to return the boolean value when it changes
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBoolChanged, bool, NewValue);

UCLASS()
class BOSS_AI_API UAsyncBoolListener : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	
	// Call this to start listening for changes on a target actor
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UAsyncBoolListener* WaitforBooleanChange(AActor* ListenActor, ATargetActor* TargetActor);

	// Output event triggered when the boolean changes
	UPROPERTY(BlueprintAssignable)
	FOnBoolChanged OnValueChanged;

	virtual void Activate() override;

private:
	// Reference to the target actor we’re listening to
	UPROPERTY()
	ATargetActor* TargetActor;
	
	// Callback for the OnBooleanChanged event
	UFUNCTION()
	void HandleChangeBool(bool NewBool);
	
};
