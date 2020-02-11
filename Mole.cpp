
#include "Mole.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Curves/CurveFloat.h"
#include "Components/TimelineComponent.h"
#include "Math/UnrealMathUtility.h"

AMole::AMole()
{
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene")); 
	RootComponent = Scene;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Scene);

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(Scene);

	Timeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimeLine"));

	InterpFunction.BindUFunction(this, FName("TimeLineFloatReturn"));
	TimeLineFinished.BindUFunction(this, FName("OnTimeLineFinished"));

	ZOffset = 50.0f;
}

void AMole::Hit(AActor* Character, AActor* HitActor, FVector NewLocation)
{
	if (Character != NULL && HitActor!= NULL) {
		if (Character->GetName().Equals(HitActor->GetName()) && Hittable) {
			Points += 10;
			Hittable = false;
			SetActorLocation(NewLocation);
		}
	}
}

void AMole::Movement()
{
	Hittable = true;

}

void AMole::TimeLineFloatReturn(float value)
{
	SetActorLocation(FMath::Lerp(StartLoc, EndLoc, value));
}

void AMole::OnTimeLineFinished()
{
	if (Timeline->GetPlaybackPosition() == 0.0f) {
		GLog->Log("Play");
		Timeline->Play();
	}
	else if (Timeline->GetPlaybackPosition() == Timeline->GetTimelineLength()) {
		GLog->Log("Reverse");
		Timeline->Reverse();
	}
}

void AMole::BeginPlay()
{
	Super::BeginPlay();

	if (FCurve) {
		Timeline->AddInterpFloat(FCurve, InterpFunction, FName("Alpha"));
		Timeline->SetTimelineFinishedFunc(TimeLineFinished);

		InitialLocation = GetActorLocation();
		StartLoc = InitialLocation;
		EndLoc = FVector(StartLoc.X, StartLoc.Y, StartLoc.Z + ZOffset);

		Timeline->SetLooping(false);
		Timeline->SetIgnoreTimeDilation(true);

		Timeline->Play();
	}
	
}

void AMole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

