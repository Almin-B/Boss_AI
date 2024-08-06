// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HealthbarWidget.h"
#include "Components/ActorComponent.h"
#include "Healthbar.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOSS_AI_API UHealthbar : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthbar();

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void UpdateHealthbar(float CurrentHealth, float MaxHealth);

	virtual void UpdateHealthbar_Implementation(float CurrentHealth, float MaxHealth);

	UFUNCTION(BlueprintCallable)
	virtual void ActivateWidget();
	
	UPROPERTY(EditDefaultsOnly, Category="Healthbar")
	TSubclassOf<UHealthbarWidget> HealthbarWidgetClass;
	UPROPERTY(EditDefaultsOnly, Category="Healthbar")
	float UpdateBackgroundHealthbarDelay = 1.0f;
	UPROPERTY(EditDefaultsOnly, Category="Healthbar")
	float UpdateBackgroundHealthbarSpeed = 0.1f;


	UHealthbarWidget* HealthbarWidget;

	bool bIsHealthbarActivated = false;

	FTimerHandle StartUpdateBackgroundHealthbarHandle;
	FTimerHandle UpdateBackgroundHealthbarHandle;
	void StartUpdateBackgroundHealthbar();
	void UpdateBackgroundHealthbar();

	float NewHealthbarPrecent;

	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
