// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomTriggerBase.h"

// Sets default values
ACustomTriggerBase::ACustomTriggerBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TriggerCollision = CreateDefaultSubobject<UBoxComponent>(FName("TriggerBoxCollison"));
	SetRootComponent(TriggerCollision);
	
}

void ACustomTriggerBase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	TriggerCollision->SetBoxExtent(TriggerSize,false);
}

void ACustomTriggerBase::OnBoxBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

// Called when the game starts or when spawned
void ACustomTriggerBase::BeginPlay()
{
	Super::BeginPlay();
	TriggerCollision->OnComponentBeginOverlap.AddDynamic(this, &ACustomTriggerBase::OnBoxBeginOverlap);
}

// Called every frame
void ACustomTriggerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

