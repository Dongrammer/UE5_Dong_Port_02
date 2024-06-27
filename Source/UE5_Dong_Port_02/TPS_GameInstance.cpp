#include "TPS_GameInstance.h"

void UTPS_GameInstance::Init()
{
	Super::Init();

	ItemComponentInstance = NewObject<UItemComponent>(this);
	//ItemComponentInstance->AddToRoot();
	UE_LOG(LogTemp, Log, TEXT("ItemInstance ID : %p"), ItemComponentInstance);
	ItemComponentInstance->SetRarityColor();
}

UItemComponent* UTPS_GameInstance::GetItemComponent()
{
	return ItemComponentInstance;
}
