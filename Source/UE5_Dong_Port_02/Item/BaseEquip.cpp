#include "Item/BaseEquip.h"
#include "Helper.h"

ABaseEquip::ABaseEquip()
{
	itemdata.ItemType = EItemType::E_Equipment;
	//DataTable = Helper::GetAsset<UDataTable>(L"/Game/Items/DT_Item_Equipment");
}

void ABaseEquip::SetEquipment()
{
	bInField = false;
	StaticMesh->SetSimulatePhysics(false);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABaseEquip::BeginPlay()
{
	Super::BeginPlay();
}

//void ABaseEquip::DataTableSetting()
//{
//	Super::DataTableSetting();
//
//	if (itemdata.ItemID == "")
//	{
//		UE_LOG(ItemLog, Warning, TEXT("ItemID Is NULL"));
//		return;
//	}
//
//	Name = DataTable->FindRow<FEquipmentItem>(itemdata.ItemID, "Row Name Error")->Name;
//	/*Rarity = DataTable->FindRow<FEquipmentItem>(itemdata.ItemID, "Row Name Error")->Rarity;
//	Texture = DataTable->FindRow<FEquipmentItem>(itemdata.ItemID, "Row Name Error")->Texture;
//	ItemSM = DataTable->FindRow<FEquipmentItem>(itemdata.ItemID, "Row Name Error")->StaticMesh;
//	Description = DataTable->FindRow<FEquipmentItem>(itemdata.ItemID, "Row Name Error")->Description;
//	Weight = DataTable->FindRow<FEquipmentItem>(itemdata.ItemID, "Row Name Error")->Weight;
//	EquipType = DataTable->FindRow<FEquipmentItem>(itemdata.ItemID, "Row Name Error")->EquipType;
//	EquipStatus = DataTable->FindRow<FEquipmentItem>(itemdata.ItemID, "Row Name Error")->EquipStatus;*/
//}
