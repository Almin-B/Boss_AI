// Fill out your copyright notice in the Description page of Project Settings.


#include "HitBox.h"
#include "Enemy_Base.h"
#include "Player_Base.h"
#include "LanceFighter.h"

// Sets default values
AHitBox::AHitBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HitBoxCollsion = CreateDefaultSubobject<UBoxComponent>(FName("HitBoxCollison"));
	SetRootComponent(HitBoxCollsion);
	HitBoxCollsion->SetCollisionResponseToAllChannels(ECR_Overlap);
}

void AHitBox::InitializeHitBox()
{
	HitBoxCollsion->SetBoxExtent(HitBoxSize, false);
	HitBoxCollsion->bHiddenInGame = !bShowHitBoxBounds;
	GetWorld()->GetTimerManager().SetTimer(DestroyTimer, this, &AHitBox::DestroyHitBox, LifeTime, false);
    
	SpawnHitBoxOverlapCheck();
	HitBoxCollsion->OnComponentBeginOverlap.AddDynamic(this, &AHitBox::OnBoxBeginOverlap);
}

void AHitBox::DestroyHitBox()
{
	this->K2_DestroyActor();
}

void AHitBox::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(bIsEnemy)
	{
		APlayer_Base* Player = Cast<APlayer_Base>(OtherActor);
		if(Player)
		{
			if (!bHasHit)
			{
				Player->TakeHit(Damage, EAttackType::Attack_1);
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("HitPlayer !!!"));
				bHasHit = true;
			}
		}
	}
	else
	{
		AEnemy_Base* Enemy = Cast<AEnemy_Base>(OtherActor);
		if (Enemy)
		{
			if(!bHasHit)
			{
				Enemy->TakeHit(Damage);	
				bHasHit = true;
			}
		}
	}
}

void AHitBox::SpawnHitBoxOverlapCheck()
{
	TArray<AActor*> OverlappingActors;
	TSubclassOf<AActor> ClassFilter;


	HitBoxCollsion->GetOverlappingActors(OverlappingActors, ClassFilter);

	for (AActor* OtherActor : OverlappingActors)
	{
		if(bIsEnemy)
		{
			APlayer_Base* Player = Cast<APlayer_Base>(OtherActor);
			if (Player)
			{
				if (!bHasHit)
				{
					Player->TakeHit(Damage, EAttackType::Attack_1);
					//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("HitPlayer !!!"));
					bHasHit = true;
					break;
				}
			}
			else
			{
				break;
			}
		}
		else
		{
			AEnemy_Base* Enemy = Cast<AEnemy_Base>(OtherActor);
			if (Enemy)
			{
				if (!bHasHit)
				{
					Enemy->TakeHit(Damage);
					bHasHit = true;
					break;
				}
				else
				{
					break;
				}
			}
		}
	}
}

// Called when the game starts or when spawned
void AHitBox::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(InitializeTimer, this, &AHitBox::InitializeHitBox, 0.1f, false);
}

// Called every frame
void AHitBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

