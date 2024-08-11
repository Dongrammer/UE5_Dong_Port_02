#include "TPS_GameInstance.h"

void UTPS_GameInstance::Init()
{
	Super::Init();

	ItemComponentInstance = NewObject<UItemComponent>(this);
	ItemComponentInstance->SetRarityColor();
}

UItemComponent* UTPS_GameInstance::GetItemComponent()
{
	return ItemComponentInstance;
}
