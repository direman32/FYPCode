#include "VRPawn.h"
#include "Camera/CameraComponent.h"
#include "MotionControllerComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "DrawDebugHelpers.h"
#include "Math/Vector.h"
#include "NavigationSystem.h"
#include "Components/SphereComponent.h"
//#include "Components/SpotLightComponent.h"

// Sets default values
AVRPawn::AVRPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(Scene);

	TeleportMarker = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TeleportMarker"));
	TeleportMarker->SetVisibility(false);
	TeleportMarker->SetupAttachment(Scene);

	TeleportBounds = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TeleportBounds"));
	TeleportBounds->SetVisibility(false);
	TeleportBounds->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	TeleportBounds->SetupAttachment(Scene);

	RightMotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightMotionController"));
	RightMotionController->SetupAttachment(Scene);
	RightMotionController->SetTrackingSource(EControllerHand::Right);

	LeftMotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftMotionController"));
	LeftMotionController->SetupAttachment(Scene);
	LeftMotionController->SetTrackingSource(EControllerHand::Left);

	RightHandSkel = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightHandSkel"));
	RightHandSkel->SetupAttachment(RightMotionController);

	LeftHandSkel = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LeftHandSkel"));
	LeftHandSkel->SetupAttachment(LeftMotionController);

	RightGrab = CreateDefaultSubobject<USphereComponent>(TEXT("RightGrab"));
	RightGrab->SetupAttachment(RightMotionController);

	LeftGrab = CreateDefaultSubobject<USphereComponent>(TEXT("LeftGrab"));
	LeftGrab->SetupAttachment(LeftMotionController);

	//Torch = CreateDefaultSubobject<USpotLightComponent>(TEXT("Torch"));
	//Torch->SetupAttachment(LeftMotionController);
}

// Called when the game starts or when spawned
void AVRPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVRPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVRPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

FVector AVRPawn::TeleportPressed(FVector Location, FVector ForwardVector)
{
	FHitResult Hit;
	FVector End = (Location + (ForwardVector * 1000.0f));
	Location = (ForwardVector * 20) + Location;
	FCollisionQueryParams CollisionParams;

	//DrawDebugLine(GetWorld(), Location, End, FColor::Green, false, 1, 0, 1);

	lastTeleportValid = true;
	TeleportMarker->SetVisibility(true);
	//Dotting against an up vector
	/*float normal = FVector::DotProduct(ForwardVector, (FVector)(0.0f, 0.0f, 1.0f));
	if (normal > .8) {
		lastTeleportValid = true;
	}
	else {
		lastTeleportValid = false;
	}*/

	bool isHit = GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECC_Visibility, CollisionParams);

	if (isHit) {
		TeleportBounds->SetVisibility(false);
		if (Hit.bBlockingHit) {
			if (GEngine) {
				return Hit.Location;
			}
		}
	}
	else {
		TeleportBounds->SetVisibility(true);
	}
	return FVector(99999.0f, 99999.0f, 99999.0f);
}

void AVRPawn::TeleportReleased(FVector CameraLocation, FVector CameraForwardVector, FVector NavLocation)
{
	TeleportMarker->SetWorldLocation(CameraLocation - (CameraForwardVector) * 5);
	TeleportMarker->SetVisibility(false);
	if (lastTeleportValid)
		TeleportTo(NavLocation, FRotator(0), true, true);
}

USkeletalMeshComponent* AVRPawn::GetHandMesh(UMotionControllerComponent* WhichController)
{
	if (WhichController->GetName().Equals("RightMotionController"))
		return RightHandSkel;
	else
		return LeftHandSkel;
}

USphereComponent* AVRPawn::GetGrabComponent(UMotionControllerComponent* WhichController)
{
	if (WhichController->GetName().Equals("RightMotionController"))
		return RightGrab;
	else
		return LeftGrab;
}
