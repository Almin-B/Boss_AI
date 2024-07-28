// Fill out your copyright notice in the Description page of Project Settings.


#include "EventTrigger_Base.h"

#include "Enemy_Base.h"
#include "Player_Base.h"

// Sets default values
AEventTrigger_Base::AEventTrigger_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	SetRootComponent(TriggerBox);
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AEventTrigger_Base::OnBoxBeginOverlap);
	TriggerBox->RegisterComponent();
}

void AEventTrigger_Base::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OnEventExecute();
}

void AEventTrigger_Base::OnEventExecute_Implementation()
{
	
}

void AEventTrigger_Base::UpdateTriggerBoxSize(FVector Size)
{
	TriggerBox->SetBoxExtent(Size);
}

// Called when the game starts or when spawned
void AEventTrigger_Base::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEventTrigger_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

