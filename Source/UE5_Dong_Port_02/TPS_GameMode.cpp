#include "TPS_GameMode.h"
#include "Helper.h"

#include "Component/ItemComponent.h"

ATPS_GameMode::ATPS_GameMode()
{
	TSubclassOf<APawn> PlayerPawnClass = Helper::GetClass<APawn>(L"/Game/Characters/Hero/BP_Hero");

	if (PlayerPawnClass != NULL)
		DefaultPawnClass = PlayerPawnClass;
}

void ATPS_GameMode::StartPlay()
{
	Super::StartPlay();

	// UItemComponent* ItemComponent = UItemComponent::GetInstance();
}
