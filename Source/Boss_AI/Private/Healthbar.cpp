// Fill out your copyright notice in the Description page of Project Settings.


#include "Healthbar.h"

#include "Player_Base.h"

// Sets default values for this component's properties
UHealthbar::UHealthbar()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UHealthbar::UpdateHealthbar_Implementation(float CurrentHealth, float MaxHealth)
{
	if(HealthbarWidget)
	{
		FVector2d InputRange = FVector2d(0.0f,MaxHealth);
		FVector2d OutputRange = FVector2d(0.0f,1.0f);

		NewHealthbarPrecent = FMath::GetMappedRangeValueClamped(InputRange,OutputRange,CurrentHealth);

		HealthbarWidget->SetHealthbarPrecent(NewHealthbarPrecent);

		//TODO: Start SmoothHealthbarUpdate
		if(GetWorld()->GetTimerManager().IsTimerActive(StartUpdateBackgroundHealthbarHandle))
		{
			GetWorld()->GetTimerManager().ClearTimer(StartUpdateBackgroundHealthbarHandle);
			GetWorld()->GetTimerManager().SetTimer(StartUpdateBackgroundHealthbarHandle,this,&UHealthbar::StartUpdateBackgroundHealthbar,UpdateBackgroundHealthbarDelay,false);
		}
		else
		{
			GetWorld()->GetTimerManager().SetTimer(StartUpdateBackgroundHealthbarHandle,this,&UHealthbar::StartUpdateBackgroundHealthbar,UpdateBackgroundHealthbarDelay,false);
		}
	}
}

void UHealthbar::ActivateWidget()
{
	
}

void UHealthbar::StartUpdateBackgroundHealthbar()
{
	GetWorld()->GetTimerManager().SetTimer(UpdateBackgroundHealthbarHandle,this,&UHealthbar::UpdateBackgroundHealthbar,GetWorld()->GetDeltaSeconds(),true);
}

void UHealthbar::UpdateBackgroundHealthbar()
{
	if(HealthbarWidget)
	{
		float alpha = 0.0f;
		alpha += UpdateBackgroundHealthbarSpeed;
		HealthbarWidget->SetBackgroundHealthbarPrecent(FMath::Lerp(HealthbarWidget->ProgressBar_Background->GetPercent(),NewHealthbarPrecent,alpha));

		if(FMath::IsNearlyEqual(alpha,1.0f,0.01f))
		{
			HealthbarWidget->SetBackgroundHealthbarPrecent(NewHealthbarPrecent);
			GetWorld()->GetTimerManager().ClearTimer(UpdateBackgroundHealthbarHandle);
		}
	}
	
}

// Called when the game starts
void UHealthbar::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHealthbar::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

