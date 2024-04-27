// Fill out your copyright notice in the Description page of Project Settings.


#include "LanceFighter.h"
#include "WindBladeAttackAnimNotify.h"
#include "SpawnCloseCombatHitboxNotify.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Player_Base.h"
#include "GlobalHelperFunctions.h"

ALanceFighter::ALanceFighter()
{
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(this->GetMesh());
	WeaponMesh->RegisterComponent();
	HitBoxSpawnPoint = CreateDefaultSubobject<USphereComponent>(TEXT("HitBoxSpawnPoint"));
	HitBoxSpawnPoint->SetupAttachment(this->GetMesh());
	HitBoxSpawnPoint->SetSphereRadius(2.0f);
	WeaponMesh->RegisterComponent();

}

void ALanceFighter::FireProjectile(FVector StartLocation, FRotator Orientation, float Speed)
{
	if (ProjectileToSpawn)
	{
		FActorSpawnParameters SpawnInfo;
		AProjectile_Base* SpawnedProjectile;
		SpawnedProjectile = GetWorld()->SpawnActor<AProjectile_Base>(ProjectileToSpawn, StartLocation, Orientation, SpawnInfo);
		if (SpawnedProjectile)
		{
			SpawnedProjectile->ProjectileSpeed = Speed;
			SpawnedProjectile->SetupProjectileMovement();

			if (MappedAttackInformation.Find(EAttackType::Attack_1))
			{
				float Damage = MappedAttackInformation.Find(EAttackType::Attack_1)->Damage;
				FVector HitboxSize = MappedAttackInformation.Find(EAttackType::Attack_1)->HitboxSize;
				float HitboxLifeTime = MappedAttackInformation.Find(EAttackType::Attack_1)->HitboxLifeTime;
				bool ShowDebug = MappedAttackInformation.Find(EAttackType::Attack_1)->bShowHitboxDebug;

				UGlobalHelperFunctions::SpawnHitBox(Damage, HitboxSize,SpawnedProjectile->GetActorLocation(), SpawnedProjectile->GetActorRotation(), HitboxLifeTime, ShowDebug, true, SpawnedProjectile,this);
			}
		}
	}

}


void ALanceFighter::PlayWindBladeAttackMontage(float AttackSpeed)
{
	if (MontageToPlay && WeaponMontageToPlay)
	{
		CharacterInstance->Montage_Play(MontageToPlay, AttackSpeed);
		WeaponInstance->Montage_Play(WeaponMontageToPlay, AttackSpeed);
	}

}

void ALanceFighter::WindBladeAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Red, TEXT("WindBaldeAttack"));
	FireProjectile(this->GetActorLocation(),UKismetMathLibrary::MakeRotFromX(this->GetActorForwardVector()),WindBladeSpeed);
	CurrentCombatAttack = EAttackType::Attack_1;
}

void ALanceFighter::OnWindBladeAttackEnd()
{
	bWindBladeAttackCompleted = true;
	bWindBladeAttackCompleted = false;
}

void ALanceFighter::InitWindBladeAnimations()
{
	MontageToPlay = *MappedAttackMontages.Find(EAttackType::Attack_1);
	WeaponMontageToPlay = *MappedAttackMontages_Weapon.Find(EAttackType::Attack_1);

	CharacterInstance = GetMesh()->GetAnimInstance();
	WeaponInstance = WeaponMesh->GetAnimInstance();

	for (FAnimNotifyEvent EventNotify : MontageToPlay->Notifies)
	{
		if (const auto AttackNotify = Cast<UWindBladeAttackAnimNotify>(EventNotify.Notify))
		{
			AttackNotify->OnNotified.AddUObject(this, &ALanceFighter::WindBladeAttack);
		}
	}

}

void ALanceFighter::InitCloseCombatAnimations()
{
	TArray<UAnimMontage*> CloseCombatMontages;

	if (*MappedAttackMontages.Find(EAttackType::Attack_2) &&
		*MappedAttackMontages.Find(EAttackType::Attack_3) &&
		*MappedAttackMontages.Find(EAttackType::Attack_4))
	{
		CloseCombatMontages.Add(*MappedAttackMontages.Find(EAttackType::Attack_2));
		CloseCombatMontages.Add(*MappedAttackMontages.Find(EAttackType::Attack_3));
		CloseCombatMontages.Add(*MappedAttackMontages.Find(EAttackType::Attack_4));
	}


	for (UAnimMontage* montages : CloseCombatMontages)
	{
		for (FAnimNotifyEvent EventNotify : montages->Notifies)
		{
			if (const auto CloseCombatNotify = Cast<USpawnCloseCombatHitboxNotify>(EventNotify.Notify))
			{
				CloseCombatNotify->OnNotified.AddUObject(this, &ALanceFighter::SpawnCloseCombatHitBox);
			}
		}
	}
}

void ALanceFighter::BeginPlay()
{
	Super::BeginPlay();
	InitWindBladeAnimations();
	InitCloseCombatAnimations();
}

void ALanceFighter::CloseCombatAttack(EAttackType Attack, float AttackSpeed)
{
	CloseCombatMontage = *MappedAttackMontages.Find(Attack);
	CloseCombatMontage_Weapon = *MappedAttackMontages_Weapon.Find(Attack);

	if (CloseCombatMontage && CloseCombatMontage_Weapon)
	{
		CharacterInstance->Montage_Play(CloseCombatMontage, AttackSpeed);
		WeaponInstance->Montage_Play(CloseCombatMontage_Weapon, AttackSpeed);
		CurrentCombatAttack = Attack;

	}
}

int ALanceFighter::ChooseCombatAttack(TArray<FCombatProbabilities> ProbabilityArray)
{
	float ProbabilitySum = 0.0f;
	int ChoosenAttackIndex;
	float RandValue; 

	for (FCombatProbabilities CombatProbability : ProbabilityArray)
	{
		ProbabilitySum += CombatProbability.Probability;
	}

	RandValue = FMath::RandRange(0.0f, ProbabilitySum);

	float Sum = 0.0f;
	
	for (FCombatProbabilities CombatProbability : ProbabilityArray)
	{
		Sum += CombatProbability.Probability;

		if (Sum >= RandValue)
		{
			ChoosenAttackIndex = CombatProbability.AttackIndex;
			break;
		}
	}
	return ChoosenAttackIndex;
}


void ALanceFighter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALanceFighter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ALanceFighter::ThrustAttack(float ThrustPower)
{
	this->LaunchCharacter(this->GetActorForwardVector() * ThrustPower, true, true);

	if (MappedAttackInformation.Find(EAttackType::Attack_Thrust))
	{
		CurrentCombatAttack = EAttackType::Attack_Thrust;

		float Damage = MappedAttackInformation.Find(EAttackType::Attack_Thrust)->Damage;
		FVector HitboxSize = MappedAttackInformation.Find(EAttackType::Attack_Thrust)->HitboxSize;
		float HitboxLifeTime = MappedAttackInformation.Find(EAttackType::Attack_Thrust)->HitboxLifeTime;
		bool ShowDebug = MappedAttackInformation.Find(EAttackType::Attack_Thrust)->bShowHitboxDebug;

		UGlobalHelperFunctions::SpawnHitBox(Damage, HitboxSize, HitBoxSpawnPoint->GetComponentLocation(), HitBoxSpawnPoint->GetComponentRotation(), HitboxLifeTime, ShowDebug, true, this,this);
	}
}

bool ALanceFighter::DetectPlayerAttack()
{
	APlayer_Base* Player = Cast<APlayer_Base>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));

	if (Player)
	{
		if (Player->bIsAttacking)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}

}


void ALanceFighter::SpawnCloseCombatHitBox()
{
	if (MappedAttackInformation.Find(CurrentCombatAttack))
	{
		float Damage = MappedAttackInformation.Find(CurrentCombatAttack)->Damage;
		FVector HitboxSize = MappedAttackInformation.Find(CurrentCombatAttack)->HitboxSize;
		float HitboxLifeTime = MappedAttackInformation.Find(CurrentCombatAttack)->HitboxLifeTime;
		bool ShowDebug = MappedAttackInformation.Find(CurrentCombatAttack)->bShowHitboxDebug;

		UGlobalHelperFunctions::SpawnHitBox(Damage, HitboxSize, HitBoxSpawnPoint->GetComponentLocation(), HitBoxSpawnPoint->GetComponentRotation(), HitboxLifeTime, ShowDebug, true, this,this);
	}

}


void ALanceFighter::StopCurrentPlayedAttackAnimMontage()
{
	if (CharacterInstance && WeaponInstance)
	{
		CharacterInstance->StopAllMontages(0.2f);
		WeaponInstance->StopAllMontages(0.2f);
	}
}


