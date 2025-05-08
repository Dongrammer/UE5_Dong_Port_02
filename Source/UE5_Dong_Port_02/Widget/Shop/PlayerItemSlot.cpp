#include "Widget/Shop/PlayerItemSlot.h"
#include "ShopItemListObject.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"

void UPlayerItemSlot::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	item = Cast<UShopItemListObject>(ListItemObject);

	if (!item)
	{
		UE_LOG(LogTemp, Warning, TEXT("InventorySlot : SlotObject is NULL !!"));
		return;
	}

	IM_ItemImage->SetBrushFromTexture(item->ItemDataTable.Texture);
	TB_ItemName->SetText(FText::FromName(item->ItemDataTable.Name));
	TB_Value->SetText(FText::FromString(FString::Printf(TEXT("( %d )"), item->Value)));
	SetCountText();
	item->DItemCountUp.BindUFunction(this, "SetCountText");
	item->DCountMultValue.BindUFunction(this, "SetValueText");
}

FReply UPlayerItemSlot::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (!bIsMouseOn) return FReply::Unhandled();

	if (item->DClickSlot.IsBound())
	{
		item->DClickSlot.Execute(item);
	}

	return FReply::Handled();
}

void UPlayerItemSlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	BO_Hovered->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	bIsMouseOn = true;
}

void UPlayerItemSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	BO_Hovered->SetVisibility(ESlateVisibility::Hidden);
	bIsMouseOn = false;
}

void UPlayerItemSlot::SetCountText()
{
	TB_ItemCount->SetText(FText::FromString(FString::Printf(TEXT("( %d )"), item->ItemCount)));
}

void UPlayerItemSlot::SetValueText()
{
	TB_Value->SetText(FText::FromString(FString::Printf(TEXT("( %d )"), item->CountMultValue)));
}
