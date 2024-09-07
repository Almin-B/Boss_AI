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
	PlayerHealthbarComp = CreateDefaultSubobject<UPlayerHealthbarComponent>(TEXT("PlayerHealthbar"));
}

// Called when the game starts or when spawned
void APlayer_Base::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	GetCharacterMovement()->MaxWalkSpeed = MaxMovementSpeed;
	AddHUDToScreen();
	PlayerHealthbarComp->ActivateWidget();
}

// Called every frame
void APlayer_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void APlayer_Base::AddHUDToScreen()
{
	HUDWidget = CreateWidget<UPlayerHUDWidget>(GetWorld(), HUDWidgetClass);
	HUDWidget->AddToViewport();
}

void APlayer_Base::LightAttack_Implementation()
{
	
}

void APlayer_Base::HeavyAttack_Implementation()
{
	
}

void APlayer_Base::StartAttack(FName AttackName)
{
	TSubclassOf<UAttack_Base> AttackClass = *PlayerAttacks.Find(AttackName);
	
	UAttack_Base* CurrentAttack = NewObject<UAttack_Base>(this,AttackClass);

	if(CurrentAttack != NULL)
	{
		CurrentAttack->Owner = this;
		CurrentAttack->AttackExecute();
	}
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
	float NewHealth = Health -= Damage;
	float NewHealthClamp = FMath::Clamp(NewHealth,0.0f,MaxHealth);
	Health = NewHealthClamp;
	PlayerHealthbarComp->UpdateHealthbar(Health,MaxHealth);
	if(Health == 0.0f)
	{
		//TODO: Player Death
	}
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

