#include "Widget/Inventory/InventoryContextMenu.h"

#include "Components/SizeBox.h"
#include "Components/Border.h"
#include "Components/VerticalBox.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "Component/InventoryComponent.h"
#include "Component/EquipComponent.h"

void UInventoryContextMenu::NativeConstruct()
{
	Super::NativeConstruct();

	// Button Bind Function
	FScriptDelegate UseClicked;
	UseClicked.BindUFunction(this, "UseItem");
	BT_Use->OnClicked.Add(UseClicked);

	FScriptDelegate EquipClicked;
	EquipClicked.BindUFunction(this, "EquipItem");
	BT_Equip->OnClicked.Add(EquipClicked);

	FScriptDelegate InfoClicked;
	InfoClicked.BindUFunction(this, "InfoItem");
	BT_Info->OnClicked.Add(InfoClicked);
}

void UInventoryContextMenu::SetInvenComp(TObjectPtr<UInventoryComponent> comp)
{
	InventoryComponent = comp;

	if (!InventoryComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("InventoryContextMenu : InventoryComponent Is NULL !!"));
		return;
	}
}

void UInventoryContextMenu::SetEquipComp(TObjectPtr<UEquipComponent> comp)
{
	EquipComponent = comp;

	if (!EquipComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("InventoryContextMenu : EquipComponent Is NULL !!"));
		return;
	}
}

void UInventoryContextMenu::SetSwitcher(uint8 num)
{

	WS_01->SetActiveWidgetIndex(num);
}

void UInventoryContextMenu::UseItem()
{
	this->SetVisibility(ESlateVisibility::Hidden);
	InventoryComponent->ItemUse(itemdata);
}

void UInventoryContextMenu::EquipItem()
{
	this->SetVisibility(ESlateVisibility::Hidden);
	EquipComponent->Equip(itemdata);
}

void UInventoryContextMenu::InfoItem()
{
	this->SetVisibility(ESlateVisibility::Hidden);
}
