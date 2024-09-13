
#include "Land/BaseVillage.h"
#include "NavModifierVolume.h"

ABaseVillage::ABaseVillage()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseVillage::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseVillage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

