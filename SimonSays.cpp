

#include "SimonSays.h"
#include "Components/ChildActorComponent.h"
#include "EngineUtils.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

ASimonSays::ASimonSays()
{
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));

	Trigger = CreateDefaultSubobject<UChildActorComponent>(TEXT("Trigger"));
	Trigger->SetupAttachment(Scene);
}

void ASimonSays::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASimonSays::SetUpButtons(FVector Loc, FRotator Rot, int index)
{
	FActorSpawnParameters SpawnParams;
	AActor* SpawnedActorRef = GetWorld()->SpawnActor<AActor>(Button, Loc, Rot);
	ButtonsMap.Add(index, Cast<ASimonSaysButton>(SpawnedActorRef));
	Sequence.Add(Cast<ASimonSaysButton>(SpawnedActorRef));
}

void ASimonSays::PlayGame()
{
	if (NumberOfPasses == Sequence.Num()) {
		FinishedGame();
	}
	else {
		started = true;
		int loopCount = 0;
		for (ASimonSaysButton* button : Sequence) {
			if (NumberOfPasses == loopCount) {
				SequenceValue = button;
				button->Display();
				NumberOfPasses++;
				PlayerInputTime = true;
				break;
			}
			loopCount++;
		}
	}
}

void ASimonSays::ButtonsAllowedToPress(bool val)  
{
	for (int i = 0; i < ButtonsMap.Num(); i++) {
		ASimonSaysButton* button = ButtonsMap.FindRef(i);
		button->Pressable(val);
	}
}

void ASimonSays::PlayerSequence()
{
	for (int i = 0; i < Sequence.Num(); i++) {
		ASimonSaysButton* button = ButtonsMap.FindRef(i);
		if (button->MaterialTouched() && !SequenceForInput.Contains(button)) {
			SequenceForInput.Add(button);
		}
	}
}

bool ASimonSays::CheckPlayerSequences()
{
	if (SequenceForInput.Num() <= NumberOfPasses) {
		for (int i = 0; i < SequenceForInput.Num(); i++) {
			if (SequenceForInput[i]->GetName().Equals(Sequence[i]->GetName())) {

			}
			else
				return false;
		}
		return true;
	}
	else {
		return false;
	}
}

void ASimonSays::ResetMaterials(int mat)
{
	for (int i = 0; i < ButtonsMap.Num(); i++) {
		ASimonSaysButton* button = ButtonsMap.FindRef(i);
		button->Material(mat);
	}
}

void ASimonSays::FinishedGame()
{
	ResetMaterials(0);
	ButtonsAllowedToPress(false);
	started = false;
	NumberOfPasses = 0;
}

void ASimonSays::PlayersInput()
{
	ButtonsAllowedToPress(true);
	PlayerSequence();
	AllCorrect = CheckPlayerSequences();
	if (AllCorrect) {
		if (SequenceForInput.Num() == NumberOfPasses) {
			continueGame = true;
		}
	}
	else
		FinishedGame();
}

void ASimonSays::ContinueGame()
{
	if (continueGame) {
		continueGame = false;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("continue"));
		ResetMaterials(0);
		ButtonsAllowedToPress(false);
		PlayerInputTime = false;
		PlayGame();
	}
}

// Called every frame
void ASimonSays::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
