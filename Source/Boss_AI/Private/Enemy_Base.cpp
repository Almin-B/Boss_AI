// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Base.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"



// Sets default values
AEnemy_Base::AEnemy_Base()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
}

void AEnemy_Base::StartAttack(FName AttackName)
{
	TSubclassOf<UAttack_Base> AttackClass = *EnemyAttacks.Find(AttackName);
	
	UAttack_Base* CurrentAttack = NewObject<UAttack_Base>(this,AttackClass);

	if(CurrentAttack != NULL)
	{
		CurrentAttack->Owner = this;
		CurrentAttack->AttackExecute();
	}
}

void AEnemy_Base::ChangeRootmotionState(EMovemntState NewMovementState)
{
	CurrentMovemntState = NewMovementState;
	GetWorldTimerManager().SetTimer(RootmotionUpdateTimeline,this, &AEnemy_Base::UpdateRootmotionAlpha,GetWorld()->GetDeltaSeconds(),true,0.0f);
}

void AEnemy_Base::UpdateRootmotionAlpha()
{
	float TargetAlpha = *MappedRootmotionData.Find(CurrentMovemntState);
	CurrentRootmotionAlpha = FMath::FInterpTo(CurrentRootmotionAlpha,TargetAlpha,GetWorld()->GetDeltaSeconds(),RootmotionUpdateSpeed);
	
	if(FMath::IsNearlyEqual(CurrentRootmotionAlpha,TargetAlpha,0.01))
	{
		GetWorldTimerManager().ClearTimer(RootmotionUpdateTimeline);
	}
}

void AEnemy_Base::TurnAround()
{
	if(!bIsTurning)
	{
		bIsTurning = true;
		TurnRotation = this->GetActorRotation() + FRotator(0,180,0);
		StartRotationZ = FMath::Abs(this->GetActorRotation().Yaw);
		EndRotationZ = FMath::Abs(TurnRotation.Yaw);
		TurnTimeline->PlayFromStart();
	}
}

void AEnemy_Base::TurnTimelineCallback(float val)
{
	if(TurnMontage)
	{
		
		FRotator CurrentRotation = this->GetActorRotation();
		float RotZ = FMath::Lerp(StartRotationZ,EndRotationZ,val);
		FRotator Rotation = FRotator(0,RotZ,0);
		
		this->SetActorRotation(Rotation);

		UAnimInstance* AnimInstance = this->GetMesh()->GetAnimInstance();
		float MontagePlayLeght = TurnMontage->GetPlayLength();
		float MappedTurnAlpha = UKismetMathLibrary::MapRangeClamped(RotZ,StartRotationZ,EndRotationZ,0.0f,MontagePlayLeght);
		
		AnimInstance->Montage_Play(TurnMontage,0.0f);
		AnimInstance->Montage_SetPosition(TurnMontage,MappedTurnAlpha);

		if(FMath::IsNearlyEqual(MappedTurnAlpha,MontagePlayLeght,0.01f))
		{
			TurnEndCallback();
		}
	}
}


void AEnemy_Base::TurnEndCallback()
{
	bIsTurning = false;
	this->GetMesh()->GetAnimInstance()->StopAllMontages(0.25f);
}

void AEnemy_Base::InitTurntimeline()
{
	if(TurnCurve)
	{
		FOnTimelineFloat OnTurnTimelineCallback;
		
		TurnTimeline = NewObject<UTimelineComponent>(this, FName("TurnTimelineAnimation"));
		TurnTimeline->CreationMethod = EComponentCreationMethod::UserConstructionScript;
		this->BlueprintCreatedComponents.Add(TurnTimeline);
		TurnTimeline->SetNetAddressable();

		TurnTimeline->SetPropertySetObject(this);
		TurnTimeline->SetDirectionPropertyName(FName("TurnTimelineDirection"));

		TurnTimeline->SetLooping(false);
		TurnTimeline->SetTimelineLength(1.0f);
		TurnTimeline->SetPlayRate(TurnTimelinePlayrate);
		TurnTimeline->SetTimelineLengthMode(ETimelineLengthMode::TL_TimelineLength);

		TurnTimeline->SetPlaybackPosition(0.0f,false);

		OnTurnTimelineCallback.BindUFunction(this, FName{ TEXT("TurnTimelineCallback")});
		TurnTimeline->AddInterpFloat(TurnCurve,OnTurnTimelineCallback);

		TurnTimeline->RegisterComponent();
		
	}
}

void AEnemy_Base::UpdateMovementState()
{

	switch (CurrentMovemntState)
	{
	case EMovemntState::Walk:
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
		GetCharacterMovement()->RotationRate = FRotator(0,RotationRate,0);
		break;
	case EMovemntState::Run:
		GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
		GetCharacterMovement()->RotationRate = FRotator(0, RotationRate, 0);
		break;
	case EMovemntState::Strave:
		GetCharacterMovement()->MaxWalkSpeed = StraveSpeed;
		GetCharacterMovement()->RotationRate = FRotator(0, 0, 0);
		break;
	case EMovemntState::Thrust:
		GetCharacterMovement()->MaxWalkSpeed = ThrustSpeed;
		GetCharacterMovement()->RotationRate = FRotator(0, 0, 0);
		break;

	}

}

void AEnemy_Base::Dodge(EDodgeDirection DodgeDirection)
{
	FVector DodgeVelocity;
	switch (DodgeDirection)
	{
	case EDodgeDirection::Left:
		DodgeVelocity = (GetActorRightVector() * -1) * DodgeSpeed;

		break;
	case EDodgeDirection::Right:
		DodgeVelocity = GetActorRightVector() * DodgeSpeed;

		break;
	case EDodgeDirection::Back:
		DodgeVelocity = (GetActorForwardVector() * -1) * DodgeSpeed;
		break;
	}

	LaunchCharacter(DodgeVelocity, true, true);
}

void AEnemy_Base::BreakGurad_Implementation()
{
	Health -= GuardBreakDamage;
	if (Health <= 0)
	{
		Death();
	}
}


void AEnemy_Base::Death_Implementation()
{
	bIsDead = true;
	this->GetController()->UnPossess();
}

void AEnemy_Base::TakeHit_Implementation(float Damage)
{


	if (!bIsDead)
	{

		if (bIsBlocking)
		{
			if (bIsGuardBroken)
			{
				bIsBlocking = false;
				Health -= Damage;
				if (Health <= 0)
				{
					Death();
				}
			}
			else
			{
				float LowHealthDamage = Damage +  (Damage * UKismetMathLibrary::MapRangeClamped(Health, 0.0f, MaxHealth, 0.25f, 0.0f));
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Dmg: %f"), LowHealthDamage));
				Guard += ((Damage + LowHealthDamage) * (GuardEfficiency * 0.01));
				BlockedHits += 1;
				if (Guard >= 100)
				{
					BreakGurad();
				}
			}
		}
		else
		{
			Health -= Damage;
			if(Health <= 0)
			{
				Death();
			}
		}
	}

}

void AEnemy_Base::ActivateEnemy_Implementation()
{

	
}

bool AEnemy_Base::IsLookingAt(FVector TargetLocation, float SightAngle)
{
	FVector DesiredLookAtDirection = UKismetMathLibrary::GetForwardVector(UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(),TargetLocation));
	FVector EnemyLookDirection = this->GetActorForwardVector();
	
	float LookAlpha = UKismetMathLibrary::Dot_VectorVector(EnemyLookDirection,DesiredLookAtDirection);
	float LookAngle = UKismetMathLibrary::DegAcos(LookAlpha);
	
	if(LookAngle >= SightAngle)
	{
		return false;
	}
	return true;
}

// Called when the game starts or when spawned
void AEnemy_Base::BeginPlay()
{
	Super::BeginPlay();
	InitTurntimeline();
	
}

// Called every frame
void AEnemy_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TurnTimeline->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, NULL);
}




