// Fill out your copyright notice in the Description page of Project Settings.


#include "WindBladeProjectile.h"

AWindBladeProjectile::AWindBladeProjectile()
{
	WindBladeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WindBlade_Mesh"));
	RootComponent = WindBladeMesh;
}

void AWindBladeProjectile::SpawnWindBladeVFX()
{


}

void AWindBladeProjectile::BeginPlay()
{
	Super::BeginPlay();
	SpawnWindBladeVFX();
}

void AWindBladeProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
