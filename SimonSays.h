#pragma once

#include "SimonSaysButton.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SimonSays.generated.h"

UCLASS()
class FYP_API ASimonSays : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASimonSays();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USceneComponent* Scene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UChildActorComponent* Trigger;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> Button;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<ASimonSaysButton*> Sequence;

	UFUNCTION(BlueprintCallable)
		void SetUpButtons(FVector Loc, FRotator Rot, int index);
	//
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool started;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool PlayerInputTime;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		ASimonSaysButton* SequenceValue;	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		ASimonSaysButton* ButtonRef;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int NumberOfPasses;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TMap<int32, ASimonSaysButton*> ButtonsMap;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool AllCorrect;	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<ASimonSaysButton*> SequenceForInput;
	//
	UFUNCTION(BlueprintCallable)
		void PlayGame();

	UFUNCTION(BlueprintCallable)
		void ButtonsAllowedToPress(bool val);

	UFUNCTION(BlueprintCallable)
		void PlayerSequence();

	UFUNCTION(BlueprintCallable)
		bool CheckPlayerSequences();

	UFUNCTION(BlueprintCallable)
	void ResetMaterials(int mat);
	
	UFUNCTION(BlueprintCallable)
		void FinishedGame();

	UFUNCTION(BlueprintCallable)
		void PlayersInput();

	UFUNCTION(BlueprintCallable)
		void ContinueGame();

	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	FTimerHandle timerHandler;
	bool continueGame;
};
