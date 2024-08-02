// Fill out your copyright notice in the Description page of Project Settings.


#include "SetBlackboardBool.h"

#include "BehaviorTree/BlackboardComponent.h"

USetBlackboardBool::USetBlackboardBool(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("SetBlackboardBool");
}

EBTNodeResult::Type USetBlackboardBool::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(BlackboardKey.SelectedKeyName,SetTo);
	
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
