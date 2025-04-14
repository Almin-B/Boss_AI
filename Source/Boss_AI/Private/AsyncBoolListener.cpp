// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncBoolListener.h"

#include "TargetActor.h"

UAsyncBoolListener* UAsyncBoolListener::WaitforBooleanChange(AActor* ListenActor, ATargetActor* TargetActor)
{
	UAsyncBoolListener* AsyncNode = NewObject<UAsyncBoolListener>();
	AsyncNode->TargetActor = TargetActor;

	return AsyncNode;
}

void UAsyncBoolListener::HandleChangeBool(bool NewBool)
{
	OnValueChanged.Broadcast(NewBool);
}

void UAsyncBoolListener::Activate()
{
	Super::Activate();

	if(TargetActor)
	{
		TargetActor->OnBooleanChanged.AddDynamic(this, &UAsyncBoolListener::HandleChangeBool);
	}
}
