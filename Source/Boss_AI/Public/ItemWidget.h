// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "ItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class BOSS_AI_API UItemWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* ItemIcon;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* ItemName;

	UFUNCTION(BlueprintCallable)
	void UpdateItemDisplay(UTexture2D* ItemTexture, FName ItemText);
	
};
