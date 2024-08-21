// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_2D.h"

#include "HeavyAttackEnd.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "HeavyAttackFollowUpNotify.h"
#include "IActionRecive.h"
#include "LanceFighter.h"
#include "MontageEndNotify.h"
#include "SpawnCloseCombatHitboxNotify.h"
#include "Components/CapsuleComponent.h"

APlayer_2D::APlayer_2D()
{
	HitBoxSpawnPoint = CreateDefaultSubobject<USphereComponent>(TEXT("HitBoxSpawnPoint"));
	HitBoxSpawnPoint->SetupAttachment(this->GetMesh());
	HitBoxSpawnPoint->SetSphereRadius(2.0f);
	FollowWalkingPath = CreateDefaultSubobject<UFollowWalkingPathComponent>(TEXT("FollowWalkingPathComponent"));
	InventoryComp = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
}

void APlayer_2D::DetectMoveDirection(float AxisValue)
{
	if(GetCurrentMoveDirectionAlpha() > 0.1f)
	{
		if(AxisValue < -0.1)
		{
			Turn();
		}
	}
	else if(GetCurrentMoveDirectionAlpha() < -0.1f)
	{
		if(AxisValue > 0.1)
		{
			Turn();
		}
	}
}

void APlayer_2D::Turn()
{
	//if(CanTurn() && TurnAnimation)
	//{
	//	if(!GetWorldTimerManager().IsTimerActive(TurnTimerHandle))
	//	{
	//		bIsTurning = true;
	//		DisableInput(UGameplayStatics::GetPlayerController(GetWorld(),0));
	//		MoveRightAxisValue = 0;
	//		this->GetCharacterMovement()->StopMovementImmediately();
	//		FollowWalkingPath->SetIsUpdateActive(false);
	//	
	//		TurnDuration = TurnAnimation->GetPlayLength() / TurnRate;
	//		GetWorldTimerManager().SetTimer(TurnTimerHandle,this,&APlayer_2D::OnTurnEnd,TurnDuration,false);
	//	}
	//}
	if(CanTurn())
	{
		this->SetActorRotation(this->GetActorRotation() + FRotator(0,180,0));
	}
}

float APlayer_2D::GetCurrentMoveDirectionAlpha()
{
	float XDirection = this->GetActorForwardVector().X;
	
	return XDirection;
}

bool APlayer_2D::CanTurn()
{
	if(!bIsTurning && !bIsSprinting && !bIsInHeavyAttack && !bIsAttacking && !bIsRolling && !bIsInLightAttack && !bIsInSpecialAttack)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool APlayer_2D::CanRoll()
{
	if(!bIsRolling && RollMontage && !bIsTurning && !bIsAttacking && !bIsInHeavyAttack && !bIsInLightAttack && !bIsInSpecialAttack)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void APlayer_2D::OnTurnEnd()
{
	bIsTurning = false;
	FollowWalkingPath->SetIsUpdateActive(true);
	
	EnableInput(UGameplayStatics::GetPlayerController(GetWorld(),0));
	
	GetWorldTimerManager().ClearTimer(TurnTimerHandle);
}

void APlayer_2D::InitMovementNotifys()
{
	if(RollMontage)
	{
		for (FAnimNotifyEvent EventNotify : RollMontage->Notifies)
		{
			if(const auto RollEndNotify = Cast<UMontageEndNotify>(EventNotify.Notify))
			{
				RollEndNotify->OnNotified.AddUObject(this, &APlayer_2D::OnRollEnd);
			}
		}
	}
}

void APlayer_2D::Roll()
{
	if(CanRoll())
	{
		bIsRolling = true;
		this->GetMesh()->GetAnimInstance()->Montage_Play(RollMontage,RollSpeed);
		this->GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel1,ECR_Ignore);
	}
}

void APlayer_2D::OnRollEnd()
{
	bIsRolling = false;
	this->GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel1,ECR_Block);
}

void APlayer_2D::HeavyAttackFollowup()
{
	if(HeavyAttackMontage && HeavyAttack_FollowUp_Montage && bIsAttacking && !bIsInLightAttack && !bIsInSpecialAttack)
	{
		if(HeavyAttackComboCount == 0)
		{
			this->GetMesh()->GetAnimInstance()->Montage_Play(HeavyAttackMontage,AttackSpeed);
			HeavyAttackComboCount++;
			CurrentPlayerAttack = EPlayerAttackType::HeavyAttack;
		}
		else if(HeavyAttackComboCount == 1)
		{
			this->GetMesh()->GetAnimInstance()->Montage_Play(HeavyAttack_FollowUp_Montage,AttackSpeed);
			CurrentPlayerAttack = EPlayerAttackType::HeavyAttack;
		}
	}
}

void APlayer_2D::HeavyAttack_Implementation()
{
	Super::HeavyAttack_Implementation();
	if(HeavyAttack_StrikeUp_Montage && !bIsAttacking && !bIsInHeavyAttack && !bIsInLightAttack && !bIsInSpecialAttack)
	{
		bIsAttacking = true;
		bIsInHeavyAttack = true;
		this->GetMesh()->GetAnimInstance()->Montage_Play(HeavyAttack_StrikeUp_Montage,AttackSpeed);
		CurrentPlayerAttack = EPlayerAttackType::HeavyAttack_StrikeUp;
	}
	
}

void APlayer_2D::InitHeavyAttackNotify()
{
	//Notify Bind for Heavy Attack Strike Up 
	if(HeavyAttack_StrikeUp_Montage)
	{
		for (FAnimNotifyEvent EventNotify : HeavyAttack_StrikeUp_Montage->Notifies)
		{
			if (const auto HeavyAttackNotify = Cast<UHeavyAttackFollowUpNotify>(EventNotify.Notify))
			{
				HeavyAttackNotify->OnNotified.AddUObject(this, &APlayer_2D::HeavyAttackFollowup);
			}
			if(const auto HeavyAttackEndNotify = Cast<UMontageEndNotify>(EventNotify.Notify))
			{
				HeavyAttackEndNotify->OnNotified.AddUObject(this, &APlayer_2D::OnHeavyAttackEnd);
			}
		}
	}
	//Notify Bind for Heavy Attack 
	if(HeavyAttackMontage)
	{
			for (FAnimNotifyEvent EventNotify : HeavyAttackMontage->Notifies)
			{
				if (const auto HeavyAttackNotify = Cast<UHeavyAttackFollowUpNotify>(EventNotify.Notify))
				{
					HeavyAttackNotify->OnNotified.AddUObject(this, &APlayer_2D::HeavyAttackFollowup);
				}
				if(const auto HeavyAttackEndNotify = Cast<UMontageEndNotify>(EventNotify.Notify))
				{
					HeavyAttackEndNotify->OnNotified.AddUObject(this, &APlayer_2D::OnHeavyAttackEnd);
				}
			}
	}
	
	//Notify Bind for Heavy Attack FollowUp
	if(HeavyAttack_FollowUp_Montage)
	{
		for (FAnimNotifyEvent EventNotify : HeavyAttack_FollowUp_Montage->Notifies)
		{
			if(const auto HeavyAttackEndNotify = Cast<UMontageEndNotify>(EventNotify.Notify))
			{
				HeavyAttackEndNotify->OnNotified.AddUObject(this, &APlayer_2D::OnHeavyAttackEnd);
			}
		}
	}
}

void APlayer_2D::OnHeavyAttackEnd()
{
	bIsAttacking = false;
	bIsInHeavyAttack = false;
	HeavyAttackComboCount = 0;
}

void APlayer_2D::SpecialAttack()
{
	if(!bIsInSpecialAttack && !bIsInLightAttack && !bIsInHeavyAttack && !bIsAttacking && SpecialAttack_Montage)
	{
		this->GetMesh()->GetAnimInstance()->Montage_Play(SpecialAttack_Montage,AttackSpeed);
		bIsInSpecialAttack = true;
		CurrentPlayerAttack = EPlayerAttackType::SpecialAttack;
	}
}

void APlayer_2D::OnSpecialAttackEnd()
{
	bIsInSpecialAttack = false;
	bIsAttacking = false;
}

void APlayer_2D::InitSpecialAttackNotify()
{
	if(SpecialAttack_Montage)
	{
		for (FAnimNotifyEvent EventNotify : SpecialAttack_Montage->Notifies)
		{
			if(const auto SpecialAttackEndNotify = Cast<UMontageEndNotify>(EventNotify.Notify))
			{
				SpecialAttackEndNotify->OnNotified.AddUObject(this, &APlayer_2D::OnSpecialAttackEnd);
			}
		}
	}
}


void APlayer_2D::LightAttack_Implementation()
{
	Super::LightAttack_Implementation();
	if(LightAttackMontage && !bIsInLightAttack && !bIsInSpecialAttack && !bIsInHeavyAttack)
	{
		this->GetMesh()->GetAnimInstance()->Montage_Play(LightAttackMontage,AttackSpeed);
		bIsInLightAttack = true;
		CurrentPlayerAttack = EPlayerAttackType::LightAttack;
	}
}

void APlayer_2D::InitLightAttackNotify()
{
	if(LightAttackMontage)
	{
		for (FAnimNotifyEvent EventNotify : LightAttackMontage->Notifies)
		{
			if(const auto LightAttackEndNotify = Cast<UMontageEndNotify>(EventNotify.Notify))
			{
				LightAttackEndNotify->OnNotified.AddUObject(this, &APlayer_2D::OnLightAttackEnd);
			}
		}
	}
}

void APlayer_2D::OnLightAttackEnd()
{
	bIsInLightAttack = false;
}


void APlayer_2D::OnSpawnHitbox()
{
	
	if(MappedAttackInformation.Find(CurrentPlayerAttack))
	{
		float Damage = MappedAttackInformation.Find(CurrentPlayerAttack)->Damage;
		FVector HitboxSize = MappedAttackInformation.Find(CurrentPlayerAttack)->HitboxSize;
		float HitboxLifeTime = MappedAttackInformation.Find(CurrentPlayerAttack)->HitboxLifeTime;
		bool ShowDebug = MappedAttackInformation.Find(CurrentPlayerAttack)->bShowHitboxDebug;
		
		UGlobalHelperFunctions::SpawnHitBox(Damage, HitboxSize, HitBoxSpawnPoint->GetComponentLocation(), HitBoxSpawnPoint->GetComponentRotation(), HitboxLifeTime, ShowDebug, false, this,this);
	}
}

 void APlayer_2D::InitHitboxNotify()
{
	TArray<UAnimMontage*> CloseCombatMontages;
	
	if (LightAttackMontage && HeavyAttackMontage && SpecialAttack_Montage && HeavyAttack_StrikeUp_Montage && HeavyAttack_FollowUp_Montage)
	{
		CloseCombatMontages.Add(LightAttackMontage);
		CloseCombatMontages.Add(HeavyAttackMontage);
		CloseCombatMontages.Add(SpecialAttack_Montage);
		CloseCombatMontages.Add(HeavyAttack_StrikeUp_Montage);
		CloseCombatMontages.Add(HeavyAttack_FollowUp_Montage);
	}

	for (UAnimMontage* montages : CloseCombatMontages)
	{
		for (FAnimNotifyEvent EventNotify : montages->Notifies)
		{
			if (const auto CloseCombatHitboxNotify = Cast<USpawnCloseCombatHitboxNotify>(EventNotify.Notify))
			{
				CloseCombatHitboxNotify->OnNotified.AddUObject(this, &APlayer_2D::OnSpawnHitbox);
			}
		}
	}
}


void APlayer_2D::BeginPlay()
{
	Super::BeginPlay();
	InitHeavyAttackNotify();
	InitLightAttackNotify();
	InitSpecialAttackNotify();
	InitMovementNotifys();
	InitHitboxNotify();
}

void APlayer_2D::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}
