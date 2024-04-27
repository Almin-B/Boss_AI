// Fill out your copyright notice in the Description page of Project Settings.


#include "GetPlayerLocation.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

UGetPlayerLocation::UGetPlayerLocation()
{
	NodeName = TEXT("GetPlayerLocation");
}

void UGetPlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	FVector PlayerLocation = Player->GetActorLocation();

	OwnerComp.GetBlackboardComponent()->SetValueAsVector(TargetLocation.SelectedKeyName, PlayerLocation);
}
