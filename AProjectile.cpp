// Fill out your copyright notice in the Description page of Project Settings.


#include "AProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Engine.h"



AProjectile::AProjectile()
{
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Sparks'"));
	PSC = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MyPSC"));
	//PSC->SetTemplate(PS.Object);

	InitialLifeSpan = 3.0f;
}

AProjectile::~AProjectile()
{
}