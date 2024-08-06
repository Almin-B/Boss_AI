// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"
#include "PlayerHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class BOSS_AI_API UPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UVerticalBox* BossHealthbarSlot;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UVerticalBox* PlayerHealthbarSlot;
};
