#include "Land/Prob/BaseProb.h"

ABaseProb::ABaseProb()
{
	PrimaryActorTick.bCanEverTick = true;

	Scene = Helper::CreateSceneComponent<USceneComponent>(this, "Scene");
	ActiveMeshIn = Helper::CreateSceneComponent<USkeletalMeshComponent>(this, "Active Mesh In", Scene);
	ActiveMeshOut = Helper::CreateSceneComponent<USkeletalMeshComponent>(this, "Active Mesh Out", Scene);
}

void ABaseProb::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseProb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseProb::Active()
{
}

