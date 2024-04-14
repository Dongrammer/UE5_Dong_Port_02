#include "Widget/Inventory/InventoryHUD.h"
#include "Components/ListView.h"
#include "Item/ItemData.h"
#include "InventorySlot.h"
#include "InventorySlotObject.h"
#include "Helper.h"


void UInventoryHUD::NativeConstruct()
{
	Super::NativeConstruct();

	OtherDataTable = Helper::GetAssetDynamic<UDataTable>(L"/Game/Items/DT_Item_Others");
	EquipmentDataTable = Helper::GetAssetDynamic<UDataTable>(L"/Game/Items/DT_Item_Others");
	WeaponDataTable = Helper::GetAssetDynamic<UDataTable>(L"/Game/Items/DT_Item_Others");

}

void UInventoryHUD::AddItem(const FItemData additem, const int count)
{
	if (additem.ItemID == "")
	{
		UE_LOG(LogTemp, Warning, TEXT("InventoryHUD : ItemID is NULL"));
		return;
	}

	int32 C = ItemList->GetNumItems();
	FString SlotNameFString = FString::Printf(TEXT("Slot_%d"), C);
	FName SlotNameFName(*SlotNameFString);
	TObjectPtr<UInventorySlotObject> ItemObject = NewObject<UInventorySlotObject>(this, UInventorySlotObject::StaticClass(), SlotNameFName);

	// 데이터 테이블에서 데이터를 읽어서 초기화.
	UDataTable* tempTable = nullptr;
	FName RowName = additem.ItemID;
	switch (additem.ItemType)
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

	if (!tempTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("DataTable : tempTable is NULL"));
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("%s"), *RowName.ToString());
	//UE_LOG(LogTemp, Log, TEXT("%s"), *tempTable->GetFName().ToString());
	FItemDataTableBase* RowInfo = tempTable->FindRow<FItemDataTableBase>(RowName, "Row Name Error");
	if (!RowInfo)
	{
		UE_LOG(LogTemp, Log, TEXT("RowInfo is NULL"));
		return;
	}
	ItemObject->ItemData.Name = RowInfo->Name;
	ItemObject->ItemData.Rarity = RowInfo->Rarity;
	ItemObject->ItemData.Texture = RowInfo->Texture;

	ItemList->AddItem(ItemObject);
}

void UInventoryHUD::CountUpItem(const int index, const int count)
{
}
