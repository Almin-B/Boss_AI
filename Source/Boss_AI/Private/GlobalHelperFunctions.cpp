// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalHelperFunctions.h"
#include "HitBox.h"
#include "Engine/World.h"
#include "LanceFighter.h"

UGlobalHelperFunctions::UGlobalHelperFunctions(const FObjectInitializer& ObjectInitializer)
{
	
}



void UGlobalHelperFunctions::SpawnHitBox(float Damage, FVector HitBoxSize, FVector Location, FRotator Rotation, float LifeTime, bool ShowDebug, bool IsFromEnemy, AActor* ParentActor, AActor* Owner)
{
	FActorSpawnParameters SpawnInfo;
	AHitBox* SpawnedHitBox;
	SpawnedHitBox = GEngine->GameViewport->GetWorld()->SpawnActor<AHitBox>(Location, Rotation, SpawnInfo);

	SpawnedHitBox->Damage = Damage;
	SpawnedHitBox->HitBoxSize = HitBoxSize;
	SpawnedHitBox->LifeTime = LifeTime;
	SpawnedHitBox->bShowHitBoxBounds = ShowDebug;
	SpawnedHitBox->bIsEnemy = IsFromEnemy;

	if (ParentActor)
	{
		SpawnedHitBox->K2_AttachRootComponentToActor(ParentActor,NAME_None,EAttachLocation::KeepWorldPosition,false);
	}
	if (Owner)
	{
		SpawnedHitBox->HitBoxOwner = Owner;

	}

}
