#include "Component/ItemComponent.h"
#include "Helper.h"

DEFINE_LOG_CATEGORY(ItemCompLog);

UItemComponent* UItemComponent::Instance = nullptr;

UItemComponent::UItemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	OtherDataTable = Helper::GetAssetDynamic<UDataTable>(L"/Game/Items/DT_Item_Other");
	EquipmentDataTable = Helper::GetAssetDynamic<UDataTable>(L"/Game/Items/DT_Item_Other");
	WeaponDataTable = Helper::GetAssetDynamic<UDataTable>(L"/Game/Items/DT_Item_Other");

	CachingDataTable();
}

UItemComponent* UItemComponent::GetInstance()
{
	if (!Instance)
	{
		Instance = NewObject<UItemComponent>();
		Instance->AddToRoot(); // 가비지 컬렉션에서 제외
	}

	return Instance;
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
		FOtherItem* data = (FOtherItem*)Row.Value;
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
		FEquipmentItem* data = (FEquipmentItem*)Row.Value;
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
		FWeaponItem* data = (FWeaponItem*)Row.Value;
		if (data)
			CachedWeaponItems.Add(Row.Key, *data);
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
			return data;
		}
	}
	default:
		break;
	}

	UE_LOG(ItemCompLog, Warning, TEXT("GetDataTableBase : ItemType Error !!"));
	return FItemDataTableBase();
}

