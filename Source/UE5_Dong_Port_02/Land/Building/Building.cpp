#include "Land/Building/Building.h"

//#include "../Trigger/Home/NPCHome_LocationVolume.h"
#include "Helper.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Character/BaseHuman.h"

ABuilding::ABuilding()
{
	PrimaryActorTick.bCanEverTick = true;

	Scene = Helper::CreateSceneComponent<USceneComponent>(this, "Scene");
	Architecture = Helper::CreateSceneComponent<USceneComponent>(this, "Architecture", Scene);
	InAndOutBox = Helper::CreateSceneComponent<UBoxComponent>(this, "InAndOutBox", Scene);
}

void ABuilding::BeginPlay()
{
	Super::BeginPlay();
	
	InAndOutBox->OnComponentBeginOverlap.AddDynamic(this, &ABuilding::ComeInCharacter);
	InAndOutBox->OnComponentEndOverlap.AddDynamic(this, &ABuilding::GetOutCharacter);
}

void ABuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABuilding::ComeInCharacter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	TObjectPtr<ABaseHuman> human = Cast<ABaseHuman>(OtherActor);

	if (human)
	{
		if (!human->IsInBuilding())
		{
			human->SetCurrentBuilding(this);
		}
	}
}

void ABuilding::GetOutCharacter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	TObjectPtr<ABaseHuman> human = Cast<ABaseHuman>(OtherActor);

	if (human)
	{
		if (human->IsInBuilding())
		{
			human->SetCurrentBuilding(nullptr);
		}
	}
}

FVector ABuilding::GetOutDoorLocation()
{
	if (!door)
	{
		UE_LOG(LogTemp, Warning, TEXT("Building : Door Is NULL !!"));
		return FVector::Zero();
	}
	
	return door->GetOutDoorLocation();
}

FVector ABuilding::GetInDoorLocation()
{
	if (!door)
	{
		UE_LOG(LogTemp, Warning, TEXT("Building : Door Is NULL !!"));
		return FVector::Zero();
	}

	return door->GetInDoorLocation();
}

void ABuilding::NPCActiveDoor()
{
}

void ABuilding::GetOut(ABaseHuman* human)
{
}

void ABuilding::GetIn(ABaseHuman* human)
{
}

