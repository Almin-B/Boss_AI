// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_Base.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
APlayer_Base::APlayer_Base()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetupStimulusSource();
}

// Called when the game starts or when spawned
void APlayer_Base::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = MaxMovementSpeed;
}

// Called every frame
void APlayer_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayer_Base::LightAttack_Implementation()
{
	
}

void APlayer_Base::HeavyAttack_Implementation()
{
	
}

bool APlayer_Base::IsAttackMontageValid()
{
	if (LightAttackMontage && HeavyAttackMontage)
	{
		return true;
	}
	else
	{	
		return false;
	}
}

bool APlayer_Base::CanMove()
{
	if (!bIsAttacking && !bIsDodging && !bIsBlocking && !bIsHit)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void APlayer_Base::TakeHit_Implementation(float Damage, EAttackType AttackType)
{
}
// Called to bind functionality to input
void APlayer_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayer_Base::SetupStimulusSource()
{
	StimulusSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus"));
	if (StimulusSource)
	{
		StimulusSource->RegisterForSense(TSubclassOf<UAISense_Sight>());
		StimulusSource->RegisterWithPerceptionSystem();
	}
}

