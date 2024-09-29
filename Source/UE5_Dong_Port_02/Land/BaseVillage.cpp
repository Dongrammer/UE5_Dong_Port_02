#include "Land/BaseVillage.h"
#include "NavModifierVolume.h"
#include "TPS_GameInstance.h"
#include "Light/BaseLight.h"
// #include "Prob/BaseProb.h"
// #include "Building/Building.h"

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
