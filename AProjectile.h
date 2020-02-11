// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AProjectile.generated.h"
#pragma once

UCLASS(config = Game)
class AProjectile : public AActor
{
	GENERATED_BODY()



public:
	AProjectile();
	~AProjectile();

	UPROPERTY(VisibleAnywhere)
		class UParticleSystemComponent* PSC;
};
