// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item_Base.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class BOSS_AI_API UItem_Base : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	FName ItemName;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UTexture2D* ItemIcon;

	UPROPERTY(BlueprintReadWrite)
	ACharacter* Owner;

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void UseItem();

	virtual void UseItem_Implementation();
};
