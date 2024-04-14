#include "Component/InventoryComponent.h"

#include "Character/BaseCharacter.h"
#include "../Public/Blueprint/UserWidget.h"
#include "../Widget/Inventory/InventoryHUD.h"
#include "Character/Hero.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}


void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ABaseHuman>(GetOwner());
}

void UInventoryComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}


void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

// true = ȹ���� �� �ִ� ����
bool UInventoryComponent::CheckWeight(float itemweight)
{
	if (MaxInvenWeight < CurrentWeight + (itemweight))
		return false;
	else
		return true;
}

void UInventoryComponent::GetItems(const FItemData itemdata, const int count)
{
	bool bfound = false;

	for (int i = 0; i < Items.Num(); i++)
	{
		if (Items[i].ItemData.ItemType == itemdata.ItemType && Items[i].ItemData.ItemID == itemdata.ItemID)
		{
			// �ִ� �������� ���� ��


			// �ִ� �������� ���� ��
			Items[i].count += count;
			bfound = true;

			if (InvenHUD) InvenHUD->CountUpItem(i, count);
			break;
		}
	}

	if (!bfound)
	{
		FItem newitem;
		newitem.ItemData = itemdata;
		newitem.count = count;
		Items.Add(newitem);

		if (InvenHUD) InvenHUD->AddItem(itemdata, count);
	}
}

