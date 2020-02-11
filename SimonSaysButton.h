// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SimonSaysButton.generated.h"

UCLASS()
class FYP_API ASimonSaysButton : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASimonSaysButton();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USceneComponent* Scene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UBoxComponent* Box;

	UPROPERTY(EditAnywhere)
		class UMaterialInterface* OnMaterial;

	UPROPERTY(EditAnywhere)
		class UMaterialInterface* OffMaterial;

	UPROPERTY(EditAnywhere)
		class UMaterialInterface* TouchedMaterial;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool allowedToPress;

	UFUNCTION(BlueprintCallable, Category = "activation")
		bool ActivateButton();

	UFUNCTION(BlueprintCallable, Category = "Material")
		bool MaterialTouched();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void resetVariables();
	void resetMaterial();
	void Pressable(bool value);
	void Display();
	void StopDisplay();
	void Material(int mat);
	bool pressed;

private:
	FTimerHandle timerHandle;
};
