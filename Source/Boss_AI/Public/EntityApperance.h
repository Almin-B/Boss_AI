// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MassEntityTemplate.h"
#include "MassEntityTraitBase.h"
#include "EntityApperance.generated.h"

UENUM(BlueprintType)
enum class EVertexAnimationState : uint8
{
	Idle    UMETA(DisplayName = "Idle"),
	Run    UMETA(DisplayName = "Run"),
	Jump    UMETA(DisplayName = "Jump"),
};

USTRUCT(BlueprintType)
struct FVertexAnimationParameters
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float StartFrame;
	UPROPERTY(EditAnywhere)
	float EndFrame;
};

USTRUCT()
struct FEntityApperanceFragment : public FMassFragment
{
	GENERATED_BODY()

	
	UPROPERTY()
	TMap<EVertexAnimationState,FVertexAnimationParameters> FragmentVertexAnmimationMap;
	UPROPERTY()
	TObjectPtr<UStaticMesh> Mesh = nullptr;
	UPROPERTY()
	FVector LastKnownLocation = FVector::ZeroVector;
	UPROPERTY()
	float FragmentEntitySize = 80.0f;
	UPROPERTY()
	bool bHasVisual = false;

	UMaterialInstanceDynamic* Material;

	TWeakObjectPtr<AActor> VisualActor;
};



UCLASS()
class BOSS_AI_API UEntityApperance : public UMassEntityTraitBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMesh> VisualMesh;
	UPROPERTY(EditAnywhere)
	TMap<EVertexAnimationState,FVertexAnimationParameters> VertexAnmimationMap;
	UPROPERTY(EditAnywhere)
	float EntitySize = 80.0f;

	virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;
};
