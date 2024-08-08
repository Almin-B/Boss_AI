// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BossHealthbarWidget.h"
#include "Healthbar.h"
#include "BossHealthbarComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BOSS_AI_API UBossHealthbarComponent : public UHealthbar
{
	GENERATED_BODY()
public:
	virtual void ActivateWidget() override;
	
	UPROPERTY(EditDefaultsOnly, Category="Healthbar")
	FText BossName;
	UPROPERTY(EditDefaultsOnly, Category="Healthbar")
	float RemoveDamageDisplayDelay = 1.0f;

	float DamageSum;

	UFUNCTION(BlueprintCallable)
	void ShowDamage(float DamageToDisplay);

	FTimerHandle ShowDamageTimerHandle;
	
	void RemoveDamageDisplay();
};
