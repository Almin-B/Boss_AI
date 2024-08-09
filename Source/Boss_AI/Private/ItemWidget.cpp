// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemWidget.h"

void UItemWidget::UpdateItemDisplay(UTexture2D* ItemTexture, FName ItemText)
{
	if(ItemTexture)
	{
		ItemIcon->SetBrushFromTexture(ItemTexture);
	}
	
	ItemName->SetText(FText::FromName(ItemText));
}
