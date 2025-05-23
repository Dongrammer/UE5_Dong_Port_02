#include "Component/ItemComponent.h"
#include "Helper.h"

DEFINE_LOG_CATEGORY(ItemCompLog);

UItemComponent::UItemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	OtherDataTable = Helper::GetAssetDynamic<UDataTable>(L"/Game/Items/DT_Item_Other");
	EquipmentDataTable = Helper::GetAssetDynamic<UDataTable>(L"/Game/Items/DT_Item_Equipment");
	WeaponDataTable = Helper::GetAssetDynamic<UDataTable>(L"/Game/Items/DT_Item_Weapon");

	CachingDataTable();
}


void UItemComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UItemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UItemComponent::CachingDataTable()
{
	// Other
	if (!OtherDataTable)
	{
		UE_LOG(ItemCompLog, Warning, TEXT("OtherDataTable Is NULL !!"));
		return;
	}
	for (auto& Row : OtherDataTable->GetRowMap())
	{
		FOtherItem* data = OtherDataTable->FindRow<FOtherItem>(Row.Key, TEXT("Caching Other Data"), true);

		if (data)
			CachedOtherItems.Add(Row.Key, *data);
	}
	
	// Equipment
	if (!EquipmentDataTable)
	{
		UE_LOG(ItemCompLog, Warning, TEXT("EquipmentDataTable Is NULL !!"));
		return;
	}
	for (auto& Row : EquipmentDataTable->GetRowMap())
	{
		FEquipmentItem* data = EquipmentDataTable->FindRow<FEquipmentItem>(Row.Key, TEXT("Caching Equipment Data"), true);
		if (data)
			CachedEquipmentItems.Add(Row.Key, *data);
	}

	// Weapon
	if (!WeaponDataTable)
	{
		UE_LOG(ItemCompLog, Warning, TEXT("WeaponDataTable Is NULL !!"));
		return;
	}
	for (auto& Row : WeaponDataTable->GetRowMap())
	{
		FWeaponItem* data = WeaponDataTable->FindRow<FWeaponItem>(Row.Key, TEXT("Caching Weapon Data"), true);
		if (data)
			CachedWeaponItems.Add(Row.Key, *data);
	}
}

void UItemComponent::SetRarityColor()
{
	// Common
	ERarity common = ERarity::E_Common;
	FLinearColor colorC = FLinearColor(0.8f, 1, 0.8f, 0.5f);
	RarityColor.Add(common, colorC);
	// Rare
	ERarity rare = ERarity::E_Rare;
	FLinearColor colorR = FLinearColor(0, 0, 1, 0.5f);
	RarityColor.Add(rare, colorR);
	// Unique
	ERarity unique = ERarity::E_Unique;
	FLinearColor colorU = FLinearColor(1, 1, 0, 0.5f);
	RarityColor.Add(unique, colorU);
}

const FLinearColor* UItemComponent::GetRarityColor(ERarity rarity)
{
	if (RarityColor.Contains(rarity))
	{
		return RarityColor.Find(rarity);
	}
	else
	{
		s = FLinearColor(0.2f, 0.8f, 0.3f, 1.0f);
		return &s;
	}
}

float UItemComponent::GetItemWeight(FItemData item)
{
	EItemType type = item.ItemType;
	FName name = item.ItemID;

	switch (type)
	{
	case EItemType::E_Other:
	{
		if (CachedOtherItems.Contains(name))
			return CachedOtherItems.FindRef(name).Weight;
	}
	case EItemType::E_Equipment:
	{
		if (CachedEquipmentItems.Contains(name))
			return CachedEquipmentItems.FindRef(name).Weight;
	}
	case EItemType::E_Weapon:
	{
		if (CachedWeaponItems.Contains(name))
			return CachedWeaponItems.FindRef(name).Weight;
	}
	}

	UE_LOG(ItemCompLog, Warning, TEXT("GetItemWeight : ItemType Error !!"));
	return 0.0f;
}

FItemDataTableBase UItemComponent::GetDataTableBase(FItemData item)
{
	EItemType type = item.ItemType;
	FName name = item.ItemID;
	FItemDataTableBase data;

	switch (type)
	{
	case EItemType::E_Equipment:
	{
		if (CachedEquipmentItems.Contains(name))
		{
			data.Name = CachedEquipmentItems.FindRef(name).Name;
			data.Rarity = CachedEquipmentItems.FindRef(name).Rarity;
			data.Texture = CachedEquipmentItems.FindRef(name).Texture;
			data.Weight = CachedEquipmentItems.FindRef(name).Weight;
			data.Description = CachedEquipmentItems.FindRef(name).Description;
			data.ItemClass = CachedEquipmentItems.FindRef(name).ItemClass;
			data.SellingValue = CachedEquipmentItems.FindRef(name).SellingValue;
			data.PurchaseValue = CachedEquipmentItems.FindRef(name).PurchaseValue;
			return data;
		}
	}
	case EItemType::E_Weapon:
	{
		if (CachedWeaponItems.Contains(name))
		{
			data.Name = CachedWeaponItems.FindRef(name).Name;
			data.Rarity = CachedWeaponItems.FindRef(name).Rarity;
			data.Texture = CachedWeaponItems.FindRef(name).Texture;
			data.Weight = CachedWeaponItems.FindRef(name).Weight;
			data.Description = CachedWeaponItems.FindRef(name).Description;
			data.ItemClass = CachedWeaponItems.FindRef(name).ItemClass;
			data.SellingValue = CachedWeaponItems.FindRef(name).SellingValue;
			data.PurchaseValue = CachedWeaponItems.FindRef(name).PurchaseValue;
			return data;
		}
	}
	case EItemType::E_SoulWeapon:
		break;
	case EItemType::E_Other:
	{
		if (CachedOtherItems.Contains(name))
		{
			data.Name = CachedOtherItems.FindRef(name).Name;
			data.Rarity = CachedOtherItems.FindRef(name).Rarity;
			data.Texture = CachedOtherItems.FindRef(name).Texture;
			data.Weight = CachedOtherItems.FindRef(name).Weight;
			data.Description = CachedOtherItems.FindRef(name).Description;
			data.ItemClass = CachedOtherItems.FindRef(name).ItemClass;
			data.SellingValue = CachedOtherItems.FindRef(name).SellingValue;
			data.PurchaseValue = CachedOtherItems.FindRef(name).PurchaseValue;
			return data;
		}
	}
	default:
	{
		UE_LOG(LogTemp, Log, TEXT(" Default!! "));
		break;
	}
	}

	UE_LOG(ItemCompLog, Warning, TEXT("GetDataTableBase : ItemType Error !!"));
	return FItemDataTableBase();
}

FName UItemComponent::GetItemName(FItemData item)
{
	switch (item.ItemType)
	{
	case EItemType::E_Equipment:
	{
		if (CachedEquipmentItems.Find(item.ItemID))
		return CachedEquipmentItems.Find(item.ItemID)->Name;
	}
	case EItemType::E_Other:
	{
		if (CachedOtherItems.Find(item.ItemID))
		return CachedOtherItems.Find(item.ItemID)->Name;
	}
	case EItemType::E_Weapon:
	{
		if (CachedWeaponItems.Find(item.ItemID))
		return CachedWeaponItems.Find(item.ItemID)->Name;
	}
	}

	return FName("Nope");
}

FEquipmentItem UItemComponent::GetEquipmentDataTable(FItemData item)
{
	FName name = item.ItemID;
	FEquipmentItem data;

	data.Name = CachedEquipmentItems.FindRef(name).Name;
	data.Rarity = CachedEquipmentItems.FindRef(name).Rarity;
	data.Texture = CachedEquipmentItems.FindRef(name).Texture;
	data.Weight = CachedEquipmentItems.FindRef(name).Weight;
	data.Description = CachedEquipmentItems.FindRef(name).Description;
	data.EquipStatus = CachedEquipmentItems.FindRef(name).EquipStatus;
	data.EquipType = CachedEquipmentItems.FindRef(name).EquipType;
	data.StaticMesh = CachedEquipmentItems.FindRef(name).StaticMesh;
	data.ItemClass = CachedEquipmentItems.FindRef(name).ItemClass;

	return data;
}

