// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleRadnomMovementTrait.h"
#include "MassEntityTemplateRegistry.h"


void USimpleRadnomMovementTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const
{
	BuildContext.AddFragment<FSimpleMovementFragment>();
	
}
