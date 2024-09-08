// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GlobalHelperFunctions.h"
#include "Enemy_Base.h"
#include "InventoryComponent.h"
#include "LanceFighter.h"
#include "PlayerHealthbarComponent.h"
#include "PlayerHUDWidget.h"
#include "Player_Base.generated.h"


UENUM(BlueprintType,Blueprintable)
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

	UPROPERTY(EditDefaultsOnly,Category="Player|UI")
	TSubclassOf<UPlayerHUDWidget> HUDWidgetClass;
	UPROPERTY(BlueprintReadWrite,Category="Player|UI")
	UPlayerHUDWidget* HUDWidget;
	

	void AddHUDToScreen();

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UPlayerHealthbarComponent* PlayerHealthbarComp;
	
	UPROPERTY(BlueprintReadWrite, Category = "Player|Health")
	float Health;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player|Health")
	float MaxHealth = 100.0f;

	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Player|Combat")
	TMap<FName,TSubclassOf<UAttack_Base>> PlayerAttacks;
	UFUNCTION(BlueprintCallable)
	void StartAttack(FName AttackName);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player|Combat")
	bool bIsAttacking;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player|Combat")
	float DashPower = 5000;
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
	bool CanMove();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void TakeHit(float Damage, EAttackType AttackType);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	class UAIPerceptionStimuliSourceComponent* StimulusSource;
	void SetupStimulusSource();


};
