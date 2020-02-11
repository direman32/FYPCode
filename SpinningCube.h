// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SpinningCube.generated.h"

UCLASS()
class FYP_API ASpinningCube : public APawn
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	// Called every frame
	ASpinningCube();

	virtual void Tick(float DeltaTime) override;

	// declare our float variables 	
	UPROPERTY(EditAnywhere, Category = Movement)
		float PitchValue;

	UPROPERTY(EditAnywhere, Category = Movement)
		float YawValue;

	UPROPERTY(EditAnywhere, Category = Movement)
		float RollValue;
};
