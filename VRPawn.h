// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "VRPawn.generated.h"

UCLASS()
class FYP_API AVRPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVRPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	bool lastTeleportValid;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USceneComponent* Scene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* TeleportMarker;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* TeleportBounds;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UMotionControllerComponent* RightMotionController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USkeletalMeshComponent* RightHandSkel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USphereComponent* RightGrab;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UMotionControllerComponent* LeftMotionController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USkeletalMeshComponent* LeftHandSkel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USphereComponent* LeftGrab;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	//	class USpotLightComponent* Torch;

	UFUNCTION(BlueprintCallable, Category = "Teleport")
		FVector TeleportPressed(FVector Location, FVector ForwardVector);

	UFUNCTION(BlueprintCallable, Category = "Teleport")
		void TeleportReleased(FVector CameraLocation, FVector CameraForwardVector, FVector NavLocation);

	UFUNCTION(BlueprintCallable, Category = "Controller")
		USkeletalMeshComponent* GetHandMesh(UMotionControllerComponent* WhichController);

	UFUNCTION(BlueprintCallable, Category = "Controller")
		USphereComponent* GetGrabComponent(UMotionControllerComponent* WhichController);
};
