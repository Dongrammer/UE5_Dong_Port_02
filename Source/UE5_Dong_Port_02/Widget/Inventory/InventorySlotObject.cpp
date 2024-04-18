#include "Widget/Inventory/InventorySlotObject.h"

void UInventorySlotObject::CountUp(int count)
{
	ItemCount += count;
	if (DItemCountUp.IsBound()) DItemCountUp.Broadcast(ItemCount);
}
