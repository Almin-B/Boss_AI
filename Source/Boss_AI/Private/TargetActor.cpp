// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetActor.h"

#include "Net/UnrealNetwork.h"

// Sets default values
ATargetActor::ATargetActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
}

void ATargetActor::SetMyBool(bool NewBool)
{
	if(HasAuthority())
	{
		MyBool = NewBool;
		OnBooleanChanged.Broadcast(MyBool);
		OnRep_MyBool();
	}
}

// Called when the game starts or when spawned
void ATargetActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATargetActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATargetActor, MyBool);
	
}

// Called every frame
void ATargetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATargetActor::OnRep_MyBool()
{
	OnBooleanChanged.Broadcast(MyBool);
}

