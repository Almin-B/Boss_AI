// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_Guts.h"

APlayer_Guts::APlayer_Guts()
{
	HitBoxSpawnPoint = CreateDefaultSubobject<USphereComponent>(TEXT("HitBoxSpawnPoint"));
	HitBoxSpawnPoint->SetupAttachment(this->GetMesh());
	HitBoxSpawnPoint->SetSphereRadius(2.0f);
}

void APlayer_Guts::BeginPlay()
{
	Super::BeginPlay();
}

void APlayer_Guts::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
