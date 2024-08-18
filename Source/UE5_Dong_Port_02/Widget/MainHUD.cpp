#include "Widget/MainHUD.h"

#include "Components/CanvasPanel.h"
#include "Widget/Equipment/EquipmentHUD.h"
#include "Widget/Inventory/InventoryHUD.h"
#include "Widget/Inventory/InventoryContextMenu.h"
#include "Widget/Status/StatusHUD.h"

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

void UMainHUD::InitHUD(TObjectPtr<UEquipmentHUD> equipHUD, TObjectPtr<UInventoryHUD> invenHUD, TObjectPtr<UStatusHUD> statusHUD)
{
	EquipHUD = equipHUD;
	InvenHUD = invenHUD;
	StatusHUD = statusHUD;
}

void UMainHUD::ToggleEquipHUD()
{
	EquipHUD->ToggleHUD();
}

void UMainHUD::ToggleInvenHUD()
{
	InvenHUD->ToggleHUD();
}

void UMainHUD::ToggleStatusHUD()
{
	StatusHUD->ToggleHUD();
}

void UMainHUD::SetAllHidden()
{
	EquipHUD->SetVisibility(ESlateVisibility::Hidden);
	InvenHUD->SetVisibility(ESlateVisibility::Hidden);
	StatusHUD->SetVisibility(ESlateVisibility::Hidden);
}

bool UMainHUD::CheckHUDsVisibility()
{
	bool b = false;
	if (!(EquipHUD->GetVisibility() == ESlateVisibility::Hidden)) b = true;
	if (!(InvenHUD->GetVisibility() == ESlateVisibility::Hidden)) b = true;
	if (!(StatusHUD->GetVisibility() == ESlateVisibility::Hidden)) b = true;

	return b;
}
