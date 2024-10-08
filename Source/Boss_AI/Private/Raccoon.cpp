// Fill out your copyright notice in the Description page of Project Settings.


#include "Raccoon.h"

#include "MontageEndNotify.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


ARaccoon::ARaccoon()
{
	FollowWalkingPath = CreateDefaultSubobject<UFollowWalkingPathComponent>(TEXT("FollowWalkingPathComponent"));
	BossHealthbar = CreateDefaultSubobject<UBossHealthbarComponent>(TEXT("BossHealthbar"));
}

void ARaccoon::TurnAround()
{
	Super::TurnAround();
	FollowWalkingPath->SetIsUpdateActive(false);
}

void ARaccoon::TurnEndCallback()
{
	Super::TurnEndCallback();
	FollowWalkingPath->SetIsUpdateActive(true);
}

void ARaccoon::StartBossEntrance_Implementation()
{
	if(BossEntranceMontage)
	{
		bIsInBossentrance = true;
		this->GetMesh()->GetAnimInstance()->Montage_Play(BossEntranceMontage);
		BossHealthbar->ActivateWidget();
		UAIBlueprintHelperLibrary::GetBlackboard(this)->SetValueAsBool("IsInCombat",bIsInBossentrance);
	}
}

void ARaccoon::InitMontagesNotify()
{
	if(BossEntranceMontage)
	{
		for (FAnimNotifyEvent EventNotify : BossEntranceMontage->Notifies)
		{
			if(const auto EntranceEndNotify = Cast<UMontageEndNotify>(EventNotify.Notify))
			{
				EntranceEndNotify->OnNotified.AddUObject(this, &ARaccoon::OnBossEndtranceEnd);
			}
		}
	}
}

void ARaccoon::OnBossEndtranceEnd()
{
	bIsInBossentrance = false;
	bIsInCombat = true;
}

void ARaccoon::TakeHit_Implementation(float Damage)
{
	//Take Damage
	Health -= Damage;

	//Display Damage in UI
	if(BossHealthbar)
	{
		BossHealthbar->UpdateHealthbar(Health,MaxHealth);
		BossHealthbar->ShowDamage(Damage);
	}

	//Take Guard Damage
	Guard += Damage * 0.25f;
	if(Guard >= 100)
	{
		BreakGurad();
	}

	// Enter second Phase
	if(Health <= MaxHealth/2.0f)
	{
		UAIBlueprintHelperLibrary::GetBlackboard(this)->SetValueAsInt("PhaseIndex",1);
	}
}

void ARaccoon::BeginPlay()
{
	Super::BeginPlay();
	UpdateMovementState();
	InitMontagesNotify();
}

void ARaccoon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
