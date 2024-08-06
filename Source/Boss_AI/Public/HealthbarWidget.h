// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "HealthbarWidget.generated.h"

/**
 * 
 */
UCLASS()
class BOSS_AI_API UHealthbarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetHealthbarPrecent(float HealthbarPrecent);
	UFUNCTION(BlueprintCallable)
	void SetBackgroundHealthbarPrecent(float HealthbarPrecent);
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UProgressBar* ProgressBar;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UProgressBar* ProgressBar_Background;
	
};
