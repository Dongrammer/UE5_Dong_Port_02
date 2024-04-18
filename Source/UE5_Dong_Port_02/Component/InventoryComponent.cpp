#include "Component/InventoryComponent.h"

#include "Character/BaseCharacter.h"
#include "../Public/Blueprint/UserWidget.h"
#include "../Widget/Inventory/InventoryHUD.h"
#include "Character/Hero.h"
#include "Item/ItemData.h"
#include "Helper.h"
#include "Kismet/GameplayStatics.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	OtherDataTable = Helper::GetAssetDynamic<UDataTable>(L"/Game/Items/DT_Item_Other");
	EquipmentDataTable = Helper::GetAssetDynamic<UDataTable>(L"/Game/Items/DT_Item_Other");
	WeaponDataTable = Helper::GetAssetDynamic<UDataTable>(L"/Game/Items/DT_Item_Other");

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

bool UInventoryComponent::CheckWeight(float itemweight)
{
	if (MaxInvenWeight < CurrentWeight + (itemweight))
		return false;
	else
		return true;
}

void UInventoryComponent::GetItems(const FItemData itemdata, const int count)
{
	RowDataInit();
	ItemDataTableSetting(itemdata);

	bool bfound = false;

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

		if (InvenHUD) InvenHUD->AddItem(RowData, count);
	}

	// Set Weight
	CurrentWeight += RowData.Weight;
	if (InvenHUD) InvenHUD->SetTextWeight(MaxInvenWeight, CurrentWeight);
}

void UInventoryComponent::ToggleInventory()
{
	if (InvenHUD)
	{
		AHero* hero = Owner->GetHero();

		if (hero)
		{
			if (InvenHUD->GetVisibility() == ESlateVisibility::Visible)
			{
				InvenHUD->SetVisibility(ESlateVisibility::Hidden);
				hero->SetMouseState(false, EInputModeType::E_GameOnly);
			}
			else
			{
				InvenHUD->SetVisibility(ESlateVisibility::Visible);
				hero->SetMouseState(true, EInputModeType::E_GameAndUIOnly, InvenHUD);
			}
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("InventoryComponent : Hero Cast Failed"));
		}
	}
}

void UInventoryComponent::InvenHUDSetting()
{
	if (InvenHUD)
	{
		InvenHUD->SetTextWeight(MaxInvenWeight, CurrentWeight);
		InvenHUD->DExit.BindUFunction(this, "ToggleInventory");
	}
}

void UInventoryComponent::ItemDataTableSetting(FItemData itemdata)
{
	//UE_LOG(LogTemp, Log, TEXT("RowData : %0.2f"), RowData.Weight);

	if (itemdata.ItemID == "")
	{
		UE_LOG(LogTemp, Warning, TEXT("InventoryHUD : ItemID is NULL"));
		return;
	}

	// Initialize by reading data from the DataTable.
	UDataTable* tempTable = nullptr;
	FName RowName = itemdata.ItemID;
	switch (itemdata.ItemType)
	{
	case EItemType::E_Equipment:
	{
		tempTable = EquipmentDataTable;
		break;
	}
	case EItemType::E_Weapon:
	{
		tempTable = WeaponDataTable;
		break;
	}
	case EItemType::E_Other:
	{
		tempTable = OtherDataTable;
		break;
	}
	default:
	{
		UE_LOG(LogTemp, Log, TEXT("InventoryHUD : Can't read ItemType"));
		break;
	}
	}

	FItemDataTableBase* tempData = tempTable->FindRow<FItemDataTableBase>(RowName, "Row Name Error");
	RowData.Name = tempData->Name;
	RowData.Rarity = tempData->Rarity;
	RowData.Description = tempData->Description;
	RowData.Weight = tempData->Weight;
	RowData.Texture = tempData->Texture;
	RowData.StaticMesh = tempData->StaticMesh;
}

void UInventoryComponent::RowDataInit()
{
	RowData.Name = "";
	RowData.Rarity = ERarity::E_None;
	RowData.Texture = nullptr;
	RowData.StaticMesh = nullptr;
	RowData.Weight = 0;
	RowData.Description = "";
}

