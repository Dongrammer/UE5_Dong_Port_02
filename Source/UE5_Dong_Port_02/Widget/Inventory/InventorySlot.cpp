#include "Widget/Inventory/InventorySlot.h"

#include "InventorySlotObject.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"


void UInventorySlot::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UInventorySlotObject* item = Cast<UInventorySlotObject>(ListItemObject);
	//ItemData = Cast<UInventorySlotObject>(ListItemObject)->ItemData;
	//if (ItemData.ItemType == EItemType::E_None) return;
	ItemName->SetText(FText::FromName(item->ItemData.Name));
	ItemMaxCount->SetText(FText::FromString(FString::Printf(TEXT("( %d )"), item->ItemData.MaxCount)));
	//ItemName->SetText(FText::FromName(ItemData.ItemID));
}
