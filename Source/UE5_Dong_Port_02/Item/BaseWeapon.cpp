#include "Item/BaseWeapon.h"

ABaseWeapon::ABaseWeapon()
{
	itemdata.ItemType = EItemType::E_Weapon;
	//DataTable = Helper::GetAsset<UDataTable>(L"/Game/Items/DT_Item_Equipment");
}

void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseWeapon::DataTableSetting()
{
}

void ABaseWeapon::SetEquipment()
{
}
