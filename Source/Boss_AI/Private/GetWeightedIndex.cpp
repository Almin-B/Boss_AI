// Fill out your copyright notice in the Description page of Project Settings.


#include "GetWeightedIndex.h"

#include "BehaviorTree/BlackboardComponent.h"

UGetWeightedIndex::UGetWeightedIndex(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("GetWeightedIndex");
}

EBTNodeResult::Type UGetWeightedIndex::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	ChoosenIndex = ChooseIndex();

	OwnerComp.GetBlackboardComponent()->SetValueAsInt(Index.SelectedKeyName,ChoosenIndex);
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

int UGetWeightedIndex::ChooseIndex()
{
	float ProbabilitySum = 0.0f;
	int i = -1;
	float RandValue;
	
	for (auto weightedIndex : IndexArray)
	{
		ProbabilitySum += weightedIndex.Weight;
	}

	RandValue = FMath::RandRange(0.0f, ProbabilitySum);

	float Sum = 0.0f;

	for (auto weightedIndex : IndexArray)
	{
		Sum += weightedIndex.Weight;

		if (Sum >= RandValue)
		{
			i = weightedIndex.Index;
			break;
		}
	}
	
	return i;
}
