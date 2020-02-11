
#include "SimonSaysButton.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/Engine.h"
#include "Engine/World.h"

// Sets default values
ASimonSaysButton::ASimonSaysButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Scene);

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetupAttachment(Scene);

	OnMaterial = CreateDefaultSubobject<UMaterialInterface>(TEXT("OnMaterial"));

	OffMaterial = CreateDefaultSubobject<UMaterialInterface>(TEXT("OffMaterial"));

	TouchedMaterial = CreateDefaultSubobject<UMaterialInterface>(TEXT("TouchedMaterial"));
}

// Called when the game starts or when spawned
void ASimonSaysButton::BeginPlay()
{
	Super::BeginPlay();
	resetMaterial();
}

bool ASimonSaysButton::ActivateButton() {
	if (allowedToPress) {
		Mesh->SetMaterial(0, TouchedMaterial);
		pressed = true;
		return true;
	}
	return false;
}

bool ASimonSaysButton::MaterialTouched()
{
	allowedToPress = true;
	return Mesh->GetMaterial(0) == TouchedMaterial;
}

void ASimonSaysButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASimonSaysButton::resetVariables()
{
	pressed = false;
	allowedToPress = false;
}

void ASimonSaysButton::resetMaterial()
{
	Mesh->SetMaterial(0, OffMaterial);
}

void ASimonSaysButton::Pressable(bool value)
{
	allowedToPress = value;
}

void ASimonSaysButton::Display()
{
	Material(1);
	GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &ASimonSaysButton::StopDisplay, 2.0f, false);
}

void ASimonSaysButton::StopDisplay()
{
	Material(0);
	allowedToPress = true;
	GetWorldTimerManager().ClearTimer(timerHandle);
}

void ASimonSaysButton::Material(int mat)
{
	if(mat == 0)
		Mesh->SetMaterial(0, OffMaterial);
	else if(mat == 1)
		Mesh->SetMaterial(0, OnMaterial);
	else
		Mesh->SetMaterial(0, TouchedMaterial);
}

