#include "Widget/MainHUD.h"

#include "Components/CanvasPanel.h"
#include "Widget/Equipment/EquipmentHUD.h"
#include "Widget/Inventory/InventoryHUD.h"
#include "Widget/Inventory/InventoryContextMenu.h"

void UMainHUD::NativeConstruct()
{
}

FReply UMainHUD::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (ContextMenu->GetVisibility() == ESlateVisibility::Visible)
		ContextMenu->SetVisibility(ESlateVisibility::Hidden);

	return FReply::Handled();
}

void UMainHUD::InitHUD(TObjectPtr<UEquipmentHUD> equipHUD, TObjectPtr<UInventoryHUD> invenHUD)
{
	EquipHUD = equipHUD;
	InvenHUD = invenHUD;
}

void UMainHUD::ToggleEquipHUD()
{
	EquipHUD->ToggleHUD();
}

void UMainHUD::ToggleInvenHUD()
{
	InvenHUD->ToggleHUD();
}

bool UMainHUD::CheckHUDsVisibility()
{
	bool b = false;
	if (!(EquipHUD->GetVisibility() == ESlateVisibility::Hidden)) b = true;
	if (!(InvenHUD->GetVisibility() == ESlateVisibility::Hidden)) b = true;

	return b;
}
