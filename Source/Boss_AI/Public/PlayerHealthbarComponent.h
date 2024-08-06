// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Healthbar.h"
#include "PlayerHealthbarComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BOSS_AI_API UPlayerHealthbarComponent : public UHealthbar
{
	GENERATED_BODY()
public:
	virtual void ActivateWidget() override;
};
