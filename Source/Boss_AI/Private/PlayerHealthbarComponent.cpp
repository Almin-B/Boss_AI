// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHealthbarComponent.h"

#include "Player_Base.h"

void UPlayerHealthbarComponent::ActivateWidget()
{
	if(!bIsHealthbarActivated && HealthbarWidgetClass)
	{
		APlayer_Base* Player = Cast<APlayer_Base>(this->GetOwner());
		if(Player && Player->HUDWidget)
		{
			HealthbarWidget = CreateWidget<UHealthbarWidget>(GetWorld(), HealthbarWidgetClass);
			Player->HUDWidget->PlayerHealthbarSlot->AddChild(HealthbarWidget);
			bIsHealthbarActivated = true;
		}
	}
}
