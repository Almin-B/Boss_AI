// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy_Base.h"
#include "Projectile_Base.h"
#include "Components/SphereComponent.h"
//#include "Animation/AnimMontage.h"

#include "LanceFighter.generated.h"

USTRUCT(BlueprintType)
struct FCombatProbabilities
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	float Probability;

	UPROPERTY(EditDefaultsOnly)
	int AttackIndex;
};

USTRUCT(BlueprintType)
struct FAttackInformation
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FVector HitboxSize;
	UPROPERTY(EditDefaultsOnly)
	float Damage;
	UPROPERTY(EditDefaultsOnly)
	float HitboxLifeTime;
	UPROPERTY(EditDefaultsOnly)
	bool bShowHitboxDebug;
};


/**
 * 
 */
UCLASS()
class BOSS_AI_API ALanceFighter : public AEnemy_Base
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALanceFighter();

	UFUNCTION(BlueprintCallable)
	void FireProjectile(FVector StartLocation,FRotator Orientation, float Speed);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LanceFighter|Combat|WindBladeAttack")
	TSubclassOf<AProjectile_Base> ProjectileToSpawn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LanceFighter|Combat")
	TMap<EAttackType, UAnimMontage*> MappedAttackMontages;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LanceFighter|Combat")
	TMap<EAttackType, UAnimMontage*> MappedAttackMontages_Weapon;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LanceFighter|Combat")
	TMap<EAttackType, FAttackInformation> MappedAttackInformation;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LanceFighter|Defense")
	UAnimMontage* HitMontage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LanceFighter|Defense")
	UAnimMontage* HitMontageWeapon;


	UFUNCTION(BlueprintImplementableEvent)
	void SpawnThrustAttackVFX();
	void ThrustAttack(float ThrustPower);

	void PlayWindBladeAttackMontage(float AttackSpeed);

	void WindBladeAttack();

	UFUNCTION(BlueprintCallable)
	void OnWindBladeAttackEnd();

	bool bWindBladeAttackCompleted = false;

	UPROPERTY(EditDefaultsOnly, Category = "LanceFighter|Combat|WindBladeAttack")
	float WindBladeSpeed;

	UPROPERTY(Instanced, EditDefaultsOnly, BlueprintReadWrite)
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly)
	USphereComponent* HitBoxSpawnPoint;

	UAnimMontage* MontageToPlay;
	UAnimMontage* WeaponMontageToPlay;

	UAnimMontage* CloseCombatMontage;
	UAnimMontage* CloseCombatMontage_Weapon;

	UAnimInstance* CharacterInstance;
	UAnimInstance* WeaponInstance;

	void InitWindBladeAnimations();

	void InitCloseCombatAnimations();

	void SpawnCloseCombatHitBox();

	void CloseCombatAttack(EAttackType Attack, float AttackSpeed);

	UFUNCTION(BlueprintCallable)
	int ChooseCombatAttack(TArray<FCombatProbabilities> ProbabilityArray);


	EAttackType CurrentCombatAttack;

	void StopCurrentPlayedAttackAnimMontage();

	//is for Close Combat
	UPROPERTY(EditDefaultsOnly, Category = "LanceFighter|Probabilities")
	TArray<FCombatProbabilities> CloseCombatProbabilities;

	//is for Longrange Combat
	UPROPERTY(EditDefaultsOnly, Category = "LanceFighter|Probabilities")
	TArray<FCombatProbabilities> LongCombatProbabilities;

	//is for determin if the enemy should use a Long range Attack or Close range Attack
	UPROPERTY(EditDefaultsOnly, Category = "LanceFighter|Probabilities")
	TArray<FCombatProbabilities> CombatProbabilities;

	bool DetectPlayerAttack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
};
