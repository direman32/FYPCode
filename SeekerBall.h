// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SeekerBall.generated.h"

UCLASS()
class FYP_API ASeekerBall : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASeekerBall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USceneComponent* Scene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector MeshLocation;
};
