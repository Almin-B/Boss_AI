// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

#include "Player_2D.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UInventoryComponent::UseItem(FName ItemName)
{
	UItem_Base* ItemToUse = *StoredItems.Find(ItemName);

	if(ItemToUse)
	{
		ItemToUse->Owner = Cast<ACharacter>(this->GetOwner());
		if(ItemToUse->Owner)
		{
			ItemToUse->UseItem();
		}
	}
}

void UInventoryComponent::AddItemToInventory(FName ItemName)
{
	TSubclassOf<UItem_Base> ItemClass = *Items.Find(ItemName);
	UItem_Base* ItemToAdd = NewObject<UItem_Base>(this,ItemClass);
	StoredItems.Add(ItemName,ItemToAdd);
}

void UInventoryComponent::UpdateItemDisplay()
{
	APlayer_2D* Owner = Cast<APlayer_2D>(this->GetOwner());
	if(Owner && ActivItem)
	{
		if(Owner->HUDWidget)
		{
			Owner->HUDWidget->ItemWidget->UpdateItemDisplay(ActivItem->ItemIcon,ActivItem->ItemName);
		}
	}
}

void UInventoryComponent::SetActivItem(FName ItemName)
{
	ActivItem = *StoredItems.Find(ItemName);
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

