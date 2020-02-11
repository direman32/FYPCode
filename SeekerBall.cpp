// Fill out your copyright notice in the Description page of Project Settings.

#include "SeekerBall.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include <Runtime/Engine/Classes/Engine/Engine.h>

// Sets default values
ASeekerBall::ASeekerBall()
	: Speed(100.0f)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Scene);
	Mesh->SetSimulatePhysics(true);
	Mesh->SetEnableGravity(false);
	Mesh->SetMassOverrideInKg("MeshMass", 1, true);

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(Scene);

	MaxSpeed = 200.0f;

	MeshLocation = GetActorLocation();
	//InitialLifeSpan = 25.0f;
}

// Called when the game starts or when spawned
void ASeekerBall::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASeekerBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	FVector Direction = PlayerPawn->GetActorLocation() - MeshLocation;
	Direction = UKismetMathLibrary::Normal(Direction);
	FVector impulse = Speed * Direction;
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, FString::Printf(TEXT("impulse: %f - %f - %f"), impulse.X, impulse.Y, impulse.Z));
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, FString::Printf(TEXT("dir: %f - %f - %f"), GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z));

	Mesh->AddImpulse(impulse);

	FVector currentVelocity = Mesh->GetPhysicsLinearVelocity();
	FVector clampedVelocity = currentVelocity.GetClampedToMaxSize(MaxSpeed);
	Mesh->SetPhysicsLinearVelocity(clampedVelocity);
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Orange, FString::Printf(TEXT("velocity: %f - %f - %f"), clampedVelocity.X, clampedVelocity.Y, clampedVelocity.Z));
}

