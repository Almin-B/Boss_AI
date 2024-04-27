// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Controller.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionComponent.h"
#include "Player_Base.h"
#include "BehaviorTree/BlackboardComponent.h"

AEnemy_Controller::AEnemy_Controller(FObjectInitializer const& ObjectInitializer)
{
	SetupPreceptionSystem();
}

void AEnemy_Controller::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (AEnemy_Base* const enemy = Cast<AEnemy_Base>(InPawn))
	{
		if (UBehaviorTree* const tree = enemy->EnemyBehaviorTree)
		{
			UBlackboardComponent* BlackBoard;
			UseBlackboard(tree->BlackboardAsset, BlackBoard);
			Blackboard = BlackBoard;
			RunBehaviorTree(tree);
		}
	}


}

void AEnemy_Controller::SetupPreceptionSystem()
{
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	if (SightConfig)
	{
		SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
		SightConfig->SightRadius = SightRadius;
		SightConfig->LoseSightRadius = SightConfig->SightRadius + 25.f;
		SightConfig->PeripheralVisionAngleDegrees = PeripheralVisionAngleDegrees;
		SightConfig->SetMaxAge(5.f);
		SightConfig->AutoSuccessRangeFromLastSeenLocation = 520.f;
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
		

		GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
		GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemy_Controller::OnTargetDetected);
		GetPerceptionComponent()->ConfigureSense((*SightConfig));
	}
}

void AEnemy_Controller::OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus)
{
	if (APlayer_Base* const player = Cast<APlayer_Base>(Actor))
	{
		GetBlackboardComponent()->SetValueAsBool("CanSeePlayer", Stimulus.WasSuccessfullySensed());
		NearTarget();
	}

}
