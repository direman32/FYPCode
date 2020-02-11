// Fill out your copyright notice in the Description page of Project Settings.


#include "SpinningCube.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"

ASpinningCube::ASpinningCube()
{
	PrimaryActorTick.bCanEverTick = true;

	PitchValue = .5f;
	YawValue = .5f;
	RollValue = .5f;

}

void ASpinningCube::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASpinningCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FRotator NewRotation = FRotator(PitchValue, YawValue, RollValue);

	FQuat QuatRotation = FQuat(NewRotation);

	AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
}
