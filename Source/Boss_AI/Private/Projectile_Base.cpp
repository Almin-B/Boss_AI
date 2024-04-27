// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile_Base.h"

// Sets default values
AProjectile_Base::AProjectile_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComponent"));
}

void AProjectile_Base::SetupProjectileMovement()
{
	if (ProjectileComponent)
	{
		ProjectileComponent->bSimulationEnabled = true;
		ProjectileComponent->Velocity = this->GetActorForwardVector() * ProjectileSpeed;
		ProjectileComponent->ProjectileGravityScale = 0;
	}
}

// Called when the game starts or when spawned
void AProjectile_Base::BeginPlay()
{
	Super::BeginPlay();
	SetupProjectileMovement();
}

// Called every frame
void AProjectile_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

