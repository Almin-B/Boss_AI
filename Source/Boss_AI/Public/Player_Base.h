// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GlobalHelperFunctions.h"
#include "Enemy_Base.h"
#include "Player_Base.generated.h"


UENUM(BlueprintType)
enum class EPlayerAttackType : uint8
{
	LightAttack UMETA(DisplayName = "LightAttack"),
	HeavyAttack_StrikeUp UMETA(DisplayName = "HeavyAttack_StrikeUp"),
	HeavyAttack UMETA(DisplayName = "HeavyAttack"),
	SpecialAttack UMETA(DisplayName = "SpecialAttack"),
};

UCLASS()
class BOSS_AI_API APlayer_Base : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayer_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void LightAttack();
	virtual void LightAttack_Implementation();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void HeavyAttack();
	virtual void HeavyAttack_Implementation();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player|Combat")
	bool bIsAttacking;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player|Combat")
	float AttackSpeed = 2;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category="Player|Combat|LightAttack")
	UAnimMontage* LightAttackMontage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player|Combat|HeavyAttack")
	UAnimMontage* HeavyAttackMontage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player|Combat")
	float DashPower = 5000;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player|Combat")
	TMap<EPlayerAttackType, FAttackInformation> MappedAttackInformation;
	UPROPERTY(BlueprintReadWrite, Category = "Player|Combat|Defense")
	bool bIsBlocking;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player|Combat|Defense")
	float Guard;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player|Combat|Defense")
	bool bIsGuardBroken;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player|Combat|Defense")
	bool bIsStunned;
	UPROPERTY(BlueprintReadWrite, Category = "Player|Combat|Defense")
	bool bIsHit;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player|Movement")
	float MaxMovementSpeed = 600;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player|Movement|Dodge")
	float DodgePower;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player|Movement|Dodge")
	bool bIsDodging;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player|Movement|Dodge")
	UAnimMontage* Dodge;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player|Camera")
	float MaxCameraPitch = -20;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player|Camera")
	float MinCameraPitch = -45;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player|Camera")
	bool bIsLockedOnEnemy;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player|Camera")
	float MaxLockDistance = 500;
	UPROPERTY(BlueprintReadWrite, Category = "Player|Camera")
	AEnemy_Base* FocusedEnemy;
	

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsAttackMontageValid();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool CanMove();

	UFUNCTION(BlueprintNativeEvent)
	void TakeHit(float Damage, EAttackType AttackType);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	class UAIPerceptionStimuliSourceComponent* StimulusSource;
	void SetupStimulusSource();


};
