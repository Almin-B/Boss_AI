// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthbarWidget.h"

void UHealthbarWidget::SetHealthbarPrecent(float HealthbarPrecent)
{
	if(ProgressBar)
	{
		ProgressBar->SetPercent(HealthbarPrecent);
	}
}

void UHealthbarWidget::SetBackgroundHealthbarPrecent(float HealthbarPrecent)
{
	if(ProgressBar_Background)
	{
		ProgressBar_Background->SetPercent(HealthbarPrecent);
	}
}
