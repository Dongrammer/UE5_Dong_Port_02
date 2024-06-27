#include "Widget/Inventory/InventorySlot.h"

#include "InventorySlotObject.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"

void UInventorySlot::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	item = Cast<UInventorySlotObject>(ListItemObject);

	if (!item)
	{
		UE_LOG(LogTemp, Warning, TEXT("InventorySlot : SlotObject is NULL !!"));
		return;
	}
	
	Text_ItemName->SetText(FText::FromName(item->ItemDataTable.Name));

	SetCountText(item->ItemCount);
	item->DItemCountUp.AddUFunction(this, "SetCountText");

	UE_LOG(LogTemp, Log, TEXT("111"));
	ItemImage->SetBrushFromTexture(item->ItemDataTable.Texture);
	Text_ItemWeight->SetText(FText::FromString(FString::Printf(TEXT("%0.2f"), item->ItemDataTable.Weight)));

	BO_Hovered->SetVisibility(ESlateVisibility::Hidden);
}

FReply UInventorySlot::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (!bIsMouseOn) return FReply::Unhandled();

	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		if (item->DItemClick.IsBound()) item->DItemClick.Broadcast(item->ItemData);
		//return FReply::Handled(); 
	}
	else if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
	{
		if (item->DItemUse.IsBound()) item->DItemUse.Broadcast(item->ItemData);
		//return FReply::Handled();
	}

	return FReply::Handled();
}

FReply UInventorySlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
		SetFocus();

	return FReply::Handled();
}

void UInventorySlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	BO_Hovered->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	bIsMouseOn = true;
}

void UInventorySlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	UE_LOG(LogTemp, Log, TEXT("Leave"));

	BO_Hovered->SetVisibility(ESlateVisibility::Hidden);
	bIsMouseOn = false;
}

void UInventorySlot::SetCountText(int count)
{
	Text_ItemCount->SetText(FText::FromString(FString::Printf(TEXT("( %d )"), count)));
}