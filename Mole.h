
#pragma once
#include "Runtime/Engine/Classes/Components/TimelineComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Mole.generated.h"

UCLASS()
class FYP_API AMole : public AActor
{
	GENERATED_BODY()
	
public:	
	AMole();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USceneComponent* Scene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USphereComponent* Sphere;

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FVector InitialLocation;

	UFUNCTION(BlueprintCallable, Category = "Overlap")
		void Hit(AActor* Character, AActor* HitActor, FVector NewLocation);

	UFUNCTION(BlueprintCallable, Category = "Movement")
		void Movement();

	UFUNCTION()
		void TimeLineFloatReturn(float value);

	UFUNCTION()
		void OnTimeLineFinished();

	/*Declare delegate function to be binded to TimeLineFloatReturn(float value)*/
	FOnTimelineFloat InterpFunction{};

	/*Declare delegate function to be binded to OnTimeLineFinished()*/
	FOnTimelineEvent TimeLineFinished{};

	class UTimelineComponent* Timeline;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UCurveFloat* FCurve;

	UPROPERTY()
		FVector StartLoc;

	UPROPERTY()
		FVector EndLoc;

	UPROPERTY(EditAnywhere, Category = "TimeLine")
		float ZOffset;

protected:

public:	
	virtual void Tick(float DeltaTime) override;

private:
	 bool Hittable;
	 float Points;
};
