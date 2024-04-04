#include "Component/InventoryComponent.h"

#include "Character/BaseCharacter.h"
#include "../Public/Blueprint/UserWidget.h"
#include "../Widget/Inventory/InventoryHUD.h"
#include "Item/BaseItem.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}


void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ABaseCharacter>(GetOwner());
}

void UInventoryComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}


void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

// true = È¹µæÇÒ ¼ö ÀÖ´Â »óÅÂ
bool UInventoryComponent::CheckWeight(float itemweight)
{
	if (MaxInvenWeight < CurrentWeight + (itemweight))
		return false;
	else
		return true;
}

void UInventoryComponent::GetItems(ABaseItem* item, int count)
{
	for (int i = 0; i < count; i++)
	{
		Items.Add(item);
	}
}

