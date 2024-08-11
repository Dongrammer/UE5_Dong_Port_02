#include "Component/InventoryComponent.h"

#include "TPS_GameInstance.h"
#include "Character/BaseCharacter.h"
#include "../Public/Blueprint/UserWidget.h"
#include "../Widget/Inventory/InventoryHUD.h"
#include "Character/Hero.h"
#include "Helper.h"
#include "Kismet/GameplayStatics.h"
#include "Component/ItemComponent.h"
#include "Widget/Inventory/InventoryContextMenu.h"
#include "Blueprint/WidgetLayoutLibrary.h"

DEFINE_LOG_CATEGORY(InventoryCompLog);

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ABaseHuman>(GetOwner());
	//ItemComponent = UItemComponent::GetInstance();
	UTPS_GameInstance* GameInstance = Cast<UTPS_GameInstance>(GetWorld()->GetGameInstance());
	if (!GameInstance)
	{
		UE_LOG(InventoryCompLog, Warning, TEXT("GameInstance Is NULL !!"));
		return;
	}

	ItemComponent = GameInstance->GetItemComponent();
	if (!ItemComponent)
	{
		UE_LOG(InventoryCompLog, Warning, TEXT("ItemComponent Is NULL !!"));
		return;
	}
}

void UInventoryComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}


void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

bool UInventoryComponent::CheckWeight(float itemweight)
{
	if (MaxInvenWeight < CurrentWeight + (itemweight))
		return false;
	else
		return true;
}

void UInventoryComponent::GetItems(const FItemData itemdata, const int count)
{
	/*RowDataInit();
	ItemDataTableSetting(itemdata);*/

	bool bfound = false;	// 인벤토리에 같은 아이템이 있는지

	for (int i = 0; i < Items.Num(); i++)
	{
		if (Items[i].ItemData.ItemType == itemdata.ItemType && Items[i].ItemData.ItemID == itemdata.ItemID)
		{
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
		if (InvenHUD) InvenHUD->AddItem(itemdata, ItemComponent->GetDataTableBase(itemdata), count);
	}

	// Set Weight
	for (int i = 0; i < count; i++)
		SetWeight(ItemComponent->GetItemWeight(itemdata));
}

void UInventoryComponent::InitInvenHUD(TObjectPtr<UInventoryHUD> hud)
{
	// HUD Setting
	InvenHUD = hud;
	if (!InvenHUD)
	{
		UE_LOG(InventoryCompLog, Warning, TEXT("InvenHUD Is NULL !!"));
		return;
	}
	InvenHUD->SetTextWeight(MaxInvenWeight, CurrentWeight);
	InvenHUD->SetVisibility(ESlateVisibility::Hidden);
	InvenHUD->InventoryComponent = this;
}

void UInventoryComponent::InitContextMenu(TObjectPtr<UInventoryContextMenu> menu)
{
	ContextMenu = menu;
	if (!ContextMenu)
	{
		UE_LOG(InventoryCompLog, Warning, TEXT("ContextMenu Is NULL !!"));
		return;
	}
	ContextMenu->SetVisibility(ESlateVisibility::Hidden);
}

void UInventoryComponent::ItemUse(FItemData item)
{
	for (int i = 0; i < Items.Num(); i++)
	{
		if (Items[i].ItemData.ItemType == item.ItemType && Items[i].ItemData.ItemID == item.ItemID)
		{
			Items[i].count--;
			SetWeight(-ItemComponent->GetItemWeight(item));

			if (Items[i].count <= 0)
			{
				if (InvenHUD) InvenHUD->RemoveItem(i);
				Items.RemoveAt(i);
			}
			else
			{
				if (InvenHUD) InvenHUD->CountUpItem(i, -1);
			}
			break;
		}
	}
}

void UInventoryComponent::ItemClick(FItemData item)
{
	if (!Owner->GetHero()) return;
	
	FVector2D MouseXY = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());

	FWidgetTransform transform;
	transform.Translation = MouseXY;
	ContextMenu->SetRenderTransform(transform);
	ContextMenu->SetItemData(item);

	switch (item.ItemType)
	{
	case EItemType::E_Other:
	{
		ContextMenu->SetSwitcher(0);
		break;
	}
	case EItemType::E_Equipment:
	{
		ContextMenu->SetSwitcher(1);
		break;
	}
	}

	ContextMenu->SetVisibility(ESlateVisibility::Visible);
}

void UInventoryComponent::SetWeight(float weight)
{
	CurrentWeight += weight;

	if (CurrentWeight < 0) CurrentWeight = 0;

	if (InvenHUD) InvenHUD->SetTextWeight(MaxInvenWeight, CurrentWeight);
}

//void UInventoryComponent::SetFocusHUD()
//{
//	TObjectPtr<AHero> hero = Cast<AHero>(Owner);
//
//	if (!hero || !InvenHUD) return;
//	
//	hero->SetMouseState(true, EInputModeType::E_UIOnly, InvenHUD);
//}
//void UInventoryComponent::SetFocusInit()
//{
//	TObjectPtr<AHero> hero = Cast<AHero>(Owner);
//
//	if (!hero || !InvenHUD) return;
//
//	hero->SetMouseState(true, EInputModeType::E_GameAndUIOnly);
//}
//
//void UInventoryComponent::ItemDataTableSetting(FItemData itemdata)
//{
//	//UE_LOG(LogTemp, Log, TEXT("RowData : %0.2f"), RowData.Weight);
//
//	if (itemdata.ItemID == "")
//	{
//		UE_LOG(InventoryCompLog, Warning, TEXT("ItemID Is NULL !!"));
//		return;
//	}
//
//	// Initialize by reading data from the DataTable.
//	UDataTable* tempTable = nullptr;
//	FName RowName = itemdata.ItemID;
//	switch (itemdata.ItemType)
//	{
//	case EItemType::E_Equipment:
//	{
//		tempTable = EquipmentDataTable;
//		break;
//	}
//	case EItemType::E_Weapon:
//	{
//		tempTable = WeaponDataTable;
//		break;
//	}
//	case EItemType::E_Other:
//	{
//		tempTable = OtherDataTable;
//		break;
//	}
//	default:
//	{
//		UE_LOG(LogTemp, Log, TEXT("InventoryHUD : Can't read ItemType"));
//		break;
//	}
//	}
//	
//	FItemDataTableBase* tempData = tempTable->FindRow<FItemDataTableBase>(RowName, "Row Name Error");
//	RowData.Name = tempData->Name;
//	RowData.Rarity = tempData->Rarity;
//	RowData.Description = tempData->Description;
//	RowData.Weight = tempData->Weight;
//	RowData.Texture = tempData->Texture;
//	RowData.StaticMesh = tempData->StaticMesh;
//}
//
//void UInventoryComponent::RowDataInit()
//{
//	RowData.Name = "";
//	RowData.Rarity = ERarity::E_None;
//	RowData.Texture = nullptr;
//	RowData.StaticMesh = nullptr;
//	RowData.Weight = 0;
//	RowData.Description = "";
//}

