#include "Item/BaseWeapon.h"
#include "Components/CapsuleComponent.h"
#include "Component/ItemComponent.h"

ABaseWeapon::ABaseWeapon()
{
	itemdata.ItemType = EItemType::E_Weapon;
	//DataTable = Helper::GetAsset<UDataTable>(L"/Game/Items/DT_Item_Equipment");

	WeaponCapsule = Helper::CreateSceneComponent<UCapsuleComponent>(this, "Weapon Capsule", FixedPoint);
}

void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	if (itemdata.ItemType == EItemType::E_None)
	{
		UE_LOG(LogTemp, Warning, TEXT("ABaseWeapon : Itemdata Is NULL !!"));
	}

	WeaponType = ItemComponent->GetWeaponType(itemdata);
}
