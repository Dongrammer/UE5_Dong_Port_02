#include "Item/BaseOther.h"
#include "ItemData.h"
#include "Helper.h"

ABaseOther::ABaseOther()
{
	itemdata.ItemType = EItemType::E_Other;
	DataTable = Helper::GetAsset<UDataTable>(L"/Game/Items/DT_Item_Other");
}

void ABaseOther::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseOther::DataTableSetting()
{
	Super::DataTableSetting();

	if (itemdata.ItemID == "")
	{
		UE_LOG(ItemLog, Warning, TEXT("ItemID Is NULL"));
		return;
	}

	Name = DataTable->FindRow<FOtherItem>(itemdata.ItemID, "Row Name Error")->Name;
	Rarity = DataTable->FindRow<FOtherItem>(itemdata.ItemID, "Row Name Error")->Rarity;
	Texture = DataTable->FindRow<FOtherItem>(itemdata.ItemID, "Row Name Error")->Texture;
	ItemSM = DataTable->FindRow<FOtherItem>(itemdata.ItemID, "Row Name Error")->StaticMesh;
	bCanUse = DataTable->FindRow<FOtherItem>(itemdata.ItemID, "Row Name Error")->bCanUse;
	Effect = DataTable->FindRow<FOtherItem>(itemdata.ItemID, "Row Name Error")->Effect;
	Duration = DataTable->FindRow<FOtherItem>(itemdata.ItemID, "Row Name Error")->Duration;
	EffectParticle = DataTable->FindRow<FOtherItem>(itemdata.ItemID, "Row Name Error")->EffectParticle;
	Description = DataTable->FindRow<FOtherItem>(itemdata.ItemID, "Row Name Error")->Description;
	Weight = DataTable->FindRow<FOtherItem>(itemdata.ItemID, "Row Name Error")->Weight;
	//ItemClass = DataTable->FindRow<FOtherItem>(itemdata.ItemID, "Row Name Error")->ItemClass;
}
