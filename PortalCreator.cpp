
#include "PortalCreator.h"

APortalCreator::APortalCreator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APortalCreator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APortalCreator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

