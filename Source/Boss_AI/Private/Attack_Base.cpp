// Fill out your copyright notice in the Description page of Project Settings.


#include "Attack_Base.h"

#include "GlobalHelperFunctions.h"
#include "SpawnCloseCombatHitboxNotify.h"
#include "GameFramework/Character.h"

UAttack_Base::UAttack_Base()
{
	
}

void UAttack_Base::AttackExecute_Implementation()
{
	if(Owner && AttackMontage)
	{
		Owner->GetMesh()->GetAnimInstance()->Montage_Play(AttackMontage,1.0f);
	}
}

void UAttack_Base::AttackEnd_Implementation()
{
}

void UAttack_Base::InterruptAttack()
{
}

void UAttack_Base::OnSpawnHitbox_Implementation()
{
	if(Owner)
	{
		if(!bIsSpawned)
		{
			UGlobalHelperFunctions::SpawnHitBox(Damage,HitboxSize,HitBoxSpawnLocation,FRotator(0,0,0),HitboxLifeTime,bShowDebug,bIsFromEnemy,Owner,Owner);
		}
	}
}

