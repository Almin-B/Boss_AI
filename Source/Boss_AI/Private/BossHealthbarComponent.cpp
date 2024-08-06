// Fill out your copyright notice in the Description page of Project Settings.


#include "BossHealthbarComponent.h"

#include "BossHealthbarWidget.h"
#include "Player_Base.h"
#include "Kismet/GameplayStatics.h"

void UBossHealthbarComponent::ActivateWidget()
{
	if(!bIsHealthbarActivated && HealthbarWidgetClass)
	{
		APlayer_Base* Player = Cast<APlayer_Base>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
		if(Player && Player->HUDWidget)
		{
			HealthbarWidget = CreateWidget<UHealthbarWidget>(GetWorld(), HealthbarWidgetClass);
			Player->HUDWidget->BossHealthbarSlot->AddChild(HealthbarWidget);

			UBossHealthbarWidget* BossHealthbarWidget = Cast<UBossHealthbarWidget>(HealthbarWidget);
			if(BossHealthbarWidget)
			{
				BossHealthbarWidget->Name->SetText(BossName);
			}
			
			bIsHealthbarActivated = true;
		}
	}
}

void UBossHealthbarComponent::ShowDamage(float DamageToDisplay)
{
	UBossHealthbarWidget* BossHealthbarWidget = Cast<UBossHealthbarWidget>(HealthbarWidget);
	if(BossHealthbarWidget)
	{
		int DamageInt = FMath::TruncToInt(DamageToDisplay);
		FString DamageDisplay = FString::FromInt(DamageInt);
		BossHealthbarWidget->Damage->SetText(FText::FromString(DamageDisplay));
		GetWorld()->GetTimerManager().SetTimer(ShowDamageTimerHandle,this,&UBossHealthbarComponent::RemoveDamageDisplay,RemoveDamageDisplayDelay,false);
	}
}

void UBossHealthbarComponent::RemoveDamageDisplay()
{
	UBossHealthbarWidget* BossHealthbarWidget = Cast<UBossHealthbarWidget>(HealthbarWidget);
	if(BossHealthbarWidget)
	{
		BossHealthbarWidget->Damage->SetText(FText());
	}
}
