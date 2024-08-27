// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCamera.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerCamera::APlayerCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Anchor = CreateDefaultSubobject<USphereComponent>(TEXT("Anchor"));
	Anchor->SetSphereRadius(5.0f);
	RootComponent = Anchor;
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->SetupAttachment(RootComponent);
	PlayerCam = CreateDefaultSubobject<UCameraComponent>( TEXT("PlayerCamera"));
	PlayerCam->SetupAttachment(CameraArm);
	
	SetupCamera();
}

void APlayerCamera::FocusActor(AActor* ActorToFocus)
{
	//FAttachmentTransformRules Rules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;
	//Rules.RotationRule = EAttachmentRule::KeepWorld;
	//this->AttachToActor(ActorToFocus,Rules);
	if(!GetWorldTimerManager().IsTimerActive(UpdateCameraHandle))
	{
		GetWorldTimerManager().SetTimer(UpdateCameraHandle,this,&APlayerCamera::UpdateCamera,CameraUpdateTick,true);
	}

	TargetActor = ActorToFocus;
	//GetWorldTimerManager().SetTimer(UpdateCameraHandle,this,&APlayerCamera::UpdateCamera,CameraUpdateTick,true);
	
}
void APlayerCamera::SetupCamera()
{
	CameraArm->TargetArmLength = CameraDistance;
	CameraArm->bDoCollisionTest = false;
	CameraArm->bEnableCameraLag = true;
	SetCameraLag(CameraLag);
	
	FRotator CameraRotation = FRotator(-CameraAngle,RotationZ,0);
	CameraArm->bInheritYaw = false;
	CameraArm->SetRelativeRotation(CameraRotation);
}

void APlayerCamera::UpdateCamera()
{
	if(TargetActor)
	{
		FVector TargetLocation = TargetActor->GetActorLocation() + (TargetActor->GetActorForwardVector() * CameraOffset);
		//this->SetActorLocation(TargetLocation);
		this->SetActorLocation(FMath::VInterpTo(this->GetActorLocation(),TargetLocation,CameraUpdateTick,CameraFollowSpeed));
	}
}

void APlayerCamera::SetCameraLag(float LagValue)
{
	CameraArm->CameraLagSpeed = LagValue;
}

// Called when the game starts or when spawned
void APlayerCamera::BeginPlay()
{
	Super::BeginPlay();
	if(ActivateOnBeginPlay && PlayerRef)
	{
		UGameplayStatics::GetPlayerController(GetWorld(),0)->SetViewTargetWithBlend(this,CameraBlendTime,VTBlend_EaseInOut);
		//calling second time SetupCamera function because calling in Construct not works all the time
		SetupCamera();
		FocusActor(PlayerRef);
	}
	else if(!PlayerRef)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Player Reference assigned"));
	}
}

// Called every frame
void APlayerCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

