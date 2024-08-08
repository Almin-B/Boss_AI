// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HealthbarWidget.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "BossHealthbarWidget.generated.h"

/**
 * 
 */
UCLASS()
class BOSS_AI_API UBossHealthbarWidget : public UHealthbarWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* Name;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* Damage;

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void PlayHelthbarEffect();
};
