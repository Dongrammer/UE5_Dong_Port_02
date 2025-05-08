#include "Land/BaseVillage.h"
#include "NavModifierVolume.h"
#include "TPS_GameInstance.h"
#include "Light/BaseLight.h"
#include "NavModifierVolume.h"
#include "Building/Building.h"
#include "Building/Inn.h"
#include "Character/HumanNPC.h"

// #include "Prob/BaseProb.h"

ABaseVillage::ABaseVillage()
{
}

void ABaseVillage::BeginPlay()
{
	Super::BeginPlay();

	// Time
	GameInstance = Cast<UTPS_GameInstance>(GetWorld()->GetGameInstance());
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("Game Instance Is NULL !!"));
		return;
	}

	GameInstance->DOneMinuteTimePass.AddUFunction(this, "OneMinuteTimePass");
}

FVector ABaseVillage::GetRandomLocation()
{
	if (!VillageVolume)
	{
		UE_LOG(LogTemp, Warning, TEXT("BaseVillage : Village Is NULL !!"));
		return FVector();
	}
	FVector BoxMin = VillageVolume->GetBounds().GetBox().Min;
	FVector BoxMax = VillageVolume->GetBounds().GetBox().Max;

	float RandomX = VillageVolume->GetActorLocation().X;
	float RandomY = VillageVolume->GetActorLocation().Y;
	float RandomZ = VillageVolume->GetActorLocation().Z;

	// LineTrace For Topography
	for (int i = 0; i < 10; i++)
	{
		float RandX = FMath::RandRange(BoxMin.X, BoxMax.X);
		float RandY = FMath::RandRange(BoxMin.Y, BoxMax.Y);
		float RandZ = BoxMax.Z;

		FHitResult hitresult;
		FVector Start = FVector(RandX, RandY, RandZ);
		FVector End = FVector(RandX, RandY, RandZ - BoxMax.Z);
		//DrawDebugLine(GetWorld(), Start, End, FColor::Blue, true, 20.0f, 0, 2.0f);

		FCollisionObjectQueryParams query;
		query.AddObjectTypesToQuery(ECC_WorldStatic);
		query.AddObjectTypesToQuery(ECC_WorldDynamic);

		bool bHit = GetWorld()->LineTraceSingleByObjectType(hitresult, Start, End, query);

		if (bHit)
		{
			TObjectPtr<ABuilding> hitBuilding = Cast<ABuilding>(hitresult.GetActor());
			if (!hitBuilding)
			{
				RandomX = RandX;
				RandomY = RandY;
				RandomZ = hitresult.Location.Z;
				break;
			}
		}
	}

	return FVector(RandomX, RandomY, RandomZ);
}

TArray<TObjectPtr<AInn>> ABaseVillage::GetInns() const
{
	if (Buildings.Num() == 0)
		return TArray<TObjectPtr<AInn>>();

	TArray<TObjectPtr<AInn>> Inns;

	for (const TObjectPtr<ABuilding> building : Buildings)
	{
		TObjectPtr<AInn> inn = Cast<AInn>(building);

		if (inn)
		{
			Inns.Add(inn);
		}
	}

	if (Inns.Num() == 0)
		return TArray<TObjectPtr<AInn>>();

	return Inns;
}

void ABaseVillage::AddVillageNPC(AHumanNPC* npc)
{
	if (VillageNPCs.Contains(npc))
	{
		UE_LOG(LogTemp, Warning, TEXT("BaseVillage : AddVillageNPC : VillageNPCs's already contain npc"));
		return;
	}

	VillageNPCs.Add(npc);
}

void ABaseVillage::OneMinuteTimePass()
{
	GlobalTime = GameInstance->GetGlobalTime();

	if (GlobalTime.CurrentTime == 1140)
	{
		for (TObjectPtr<ABaseLight> light : Lights)
		{
			light->Active();
		}
	}
	else if (GlobalTime.CurrentTime == 420)
	{
		for (TObjectPtr<ABaseLight> light : Lights)
		{
			light->Deactive();
		}
	}
}
