#include "Widget/Inventory/InventorySlot.h"

#include "InventorySlotObject.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"


void UInventorySlot::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UInventorySlotObject* item = Cast<UInventorySlotObject>(ListItemObject);

	if (!item)
	{
		UE_LOG(LogTemp, Warning, TEXT("InventorySlot : SlotObject is NULL !!"));
		return;
	}
	
	Text_ItemName->SetText(FText::FromName(item->ItemData.Name));

	SetCountText(item->ItemCount);
	item->DItemCountUp.AddUFunction(this, "SetCountText");

	UE_LOG(LogTemp, Log, TEXT("111"));
	ItemImage->SetBrushFromTexture(item->ItemData.Texture);
	Text_ItemWeight->SetText(FText::FromString(FString::Printf(TEXT("%0.2f"), item->ItemData.Weight)));
}

void UInventorySlot::SetCountText(int count)
{
	Text_ItemCount->SetText(FText::FromString(FString::Printf(TEXT("( %d )"), count)));
}
