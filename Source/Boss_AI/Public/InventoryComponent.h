// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item_Base.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOSS_AI_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Inventory|Items")
	TMap<FName,TSubclassOf<UItem_Base>> Items;
	UPROPERTY(BlueprintReadWrite)
	TMap<FName,UItem_Base*> StoredItems;
	UPROPERTY(BlueprintReadWrite)
	UItem_Base* ActivItem;

	UFUNCTION(BlueprintCallable)
	void UseItem(FName ItemName);

	UFUNCTION(BlueprintCallable)
	void AddItemToInventory(FName ItemName);

	UFUNCTION(BlueprintCallable)
	void UpdateItemDisplay();

	UFUNCTION(BlueprintCallable)
	void SetActivItem(FName ItemName);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
