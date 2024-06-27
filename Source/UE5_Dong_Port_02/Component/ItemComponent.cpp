#include "Component/ItemComponent.h"
#include "Helper.h"

DEFINE_LOG_CATEGORY(ItemCompLog);

//UItemComponent* UItemComponent::Instance = nullptr;

UItemComponent::UItemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	OtherDataTable = Helper::GetAssetDynamic<UDataTable>(L"/Game/Items/DT_Item_Other");
	EquipmentDataTable = Helper::GetAssetDynamic<UDataTable>(L"/Game/Items/DT_Item_Equipment");
	WeaponDataTable = Helper::GetAssetDynamic<UDataTable>(L"/Game/Items/DT_Item_Other");

	CachingDataTable();
}

//UItemComponent* UItemComponent::GetInstance()
//{
//	if (!Instance)
//	{
//		Instance = NewObject<UItemComponent>();
//		Instance->AddToRoot(); // 가비지 컬렉션에서 제외
//		UE_LOG(LogTemp, Log, TEXT("GetInstance: Created new instance: %p"), Instance);
//	}
//	else
//	{
//		UE_LOG(LogTemp, Log, TEXT("GetInstance: Using existing instance: %p"), Instance);
//	}
//
//	return Instance;
//}

void UItemComponent::BeginPlay()
{
	Super::BeginPlay();

	/*if (!Instance)
	{
		Instance = this;
		SetRarityColor();
	}*/

	//SetRarityColor();
}

void UItemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//UE_LOG(LogTemp, Log, TEXT("%d"), RarityColor.Num());
	//UE_LOG(LogTemp, Log, TEXT("%0.2f, %0.2f, %0.2f"), RarityColor.FindRef(ERarity::E_Common).R, RarityColor.FindRef(ERarity::E_Common).G, RarityColor.FindRef(ERarity::E_Common).B);
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

void UItemComponent::SetRarityColor()
{
	UE_LOG(LogTemp, Log, TEXT("SetRarityColor called on instance: %p"), this);
	// Common
	ERarity common = ERarity::E_Common;
	FLinearColor colorC = FLinearColor(0.8f, 1, 0.8f, 0.5f);
	RarityColor.Add(common, colorC);
	UE_LOG(LogTemp, Log, TEXT("Added Common color: %0.2f, %0.2f, %0.2f"), colorC.R, colorC.G, colorC.B);

	// Rare
	ERarity rare = ERarity::E_Rare;
	FLinearColor colorR = FLinearColor(0, 0, 1, 0.5f);
	RarityColor.Add(rare, colorR);
	UE_LOG(LogTemp, Log, TEXT("Added Rare color: %0.2f, %0.2f, %0.2f"), colorR.R, colorR.G, colorR.B);

	// Unique
	ERarity unique = ERarity::E_Unique;
	FLinearColor colorU = FLinearColor(1, 1, 0, 0.5f);
	RarityColor.Add(unique, colorU);
	UE_LOG(LogTemp, Log, TEXT("Added Unique color: %0.2f, %0.2f, %0.2f"), colorU.R, colorU.G, colorU.B);


	for (const TPair<ERarity, FLinearColor>& Pair : RarityColor)
	{
		UE_LOG(LogTemp, Log, TEXT("SetRarityColor - Key: %d, Value: %0.2f, %0.2f, %0.2f"), (int32)Pair.Key, Pair.Value.R, Pair.Value.G, Pair.Value.B);
	}
}

const FLinearColor* UItemComponent::GetRarityColor(ERarity rarity)
{
	UE_LOG(LogTemp, Log, TEXT("GetRarityColor called on instance: %p"), this);
	UE_LOG(LogTemp, Log, TEXT("GetRarityColor - Map size: %d"), RarityColor.Num());

	for (const TPair<ERarity, FLinearColor>& Pair : RarityColor)
	{
		UE_LOG(LogTemp, Log, TEXT("GetRarityColor - Key: %d, Value: %0.2f, %0.2f, %0.2f"), (int32)Pair.Key, Pair.Value.R, Pair.Value.G, Pair.Value.B);
	}

	if (rarity == ERarity::E_Common)
	{
		UE_LOG(LogTemp, Log, TEXT("Comp : Common"));
	}
	else if (rarity == ERarity::E_Rare)
	{
		UE_LOG(LogTemp, Log, TEXT("Comp : Rare"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Comp : Fuck"));
	}

	if (RarityColor.Contains(rarity))
	{
		UE_LOG(LogTemp, Log, TEXT("GetRarityColor - Contains key: %d"), (int32)rarity);
		return RarityColor.Find(rarity);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("GetRarityColor - Does not contain key: %d"), (int32)rarity);
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

FEquipmentItem UItemComponent::GetEquipmentDataTable(FItemData item)
{
	EItemType type = item.ItemType;
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

	return data;
}

