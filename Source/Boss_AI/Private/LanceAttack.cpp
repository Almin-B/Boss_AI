// Fill out your copyright notice in the Description page of Project Settings.


#include "LanceAttack.h"
#include "LanceFighter.h"
#include "Kismet/GameplayStatics.h"

ULanceAttack::ULanceAttack(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("LanceAttack");
}

EBTNodeResult::Type ULanceAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	bool result;

	switch (AttackType)
	{
		//Thrust Attack
		case EAttackType::Attack_Thrust:

			result = ExecuteThrustAttack(OwnerComp);

			if (result)
			{
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
			else
			{
				return EBTNodeResult::Failed;
			}
			break;

		//Fire Wind-Blade Attack
		case EAttackType::Attack_1:

			result = ExecuteWindProjectileAttack(OwnerComp);

			if (result)
			{
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
				
			}
			else
			{
				return EBTNodeResult::InProgress;	
			}

		case EAttackType::Attack_2:

			result = ExecuteCloseCombatAttack(OwnerComp, EAttackType::Attack_2);

			if (result)
			{
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
			else
			{
				return EBTNodeResult::Failed;
			}

		case EAttackType::Attack_3:

			result = ExecuteCloseCombatAttack(OwnerComp, EAttackType::Attack_3);

			if (result)
			{
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
			else
			{
				return EBTNodeResult::Failed;
			}

		case EAttackType::Attack_4:

			result = ExecuteCloseCombatAttack(OwnerComp, EAttackType::Attack_4);

			if (result)
			{
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
			else
			{
				return EBTNodeResult::Failed;
			}

			break;
	}


	return EBTNodeResult::Failed;
}

bool ULanceAttack::ExecuteThrustAttack(UBehaviorTreeComponent& OwnerComp)
{
	AAIController* AIOwner = OwnerComp.GetAIOwner();
	APawn* OwnerPawn = AIOwner->GetPawn();

	ALanceFighter* Enemy = Cast<ALanceFighter>(OwnerPawn);

	FVector ThrustLocation;

	ThrustLocation = OwnerPawn->GetActorLocation() + (OwnerPawn->GetActorForwardVector() * Enemy->ThrustDistance);



	float Distance = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(GetSelectedBlackboardKey());

	if (Distance > MinDistacne && Distance < MaxDistacne)
	{
		
		Enemy->SpawnThrustAttackVFX();
		if (UseDash)
		{
			Enemy->ThrustAttack(DashPower);
		}
		else
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(AIOwner, ThrustLocation);

		}

		return true;
	}
	else
	{
		return false;
	}

}

bool ULanceAttack::ExecuteWindProjectileAttack(UBehaviorTreeComponent& OwnerComp)
{
	AAIController* AIOwner = OwnerComp.GetAIOwner();
	APawn* OwnerPawn = AIOwner->GetPawn();

	ALanceFighter* Enemy = Cast<ALanceFighter>(OwnerPawn);

	if (Enemy)
	{
		
		if (!Enemy->bWindBladeAttackCompleted)
		{
			
			Enemy->PlayWindBladeAttackMontage(AttackSpeed);

			if (Enemy->bWindBladeAttackCompleted)
			{
				return true;
			}
		}
		return false;
	}
	return false;
}

bool ULanceAttack::ExecuteCloseCombatAttack(UBehaviorTreeComponent& OwnerComp, EAttackType Attack)
{
	AAIController* AIOwner = OwnerComp.GetAIOwner();
	APawn* OwnerPawn = AIOwner->GetPawn();

	ALanceFighter* Enemy = Cast<ALanceFighter>(OwnerPawn);

	if (Enemy)
	{
		Enemy->CloseCombatAttack(Attack,AttackSpeed);
		return true;
	}

	return false;
}



