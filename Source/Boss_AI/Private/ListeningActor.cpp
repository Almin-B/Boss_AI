// Fill out your copyright notice in the Description page of Project Settings.


#include "ListeningActor.h"

// Sets default values
AListeningActor::AListeningActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = false;

}

// Called when the game starts or when spawned
void AListeningActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AListeningActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

