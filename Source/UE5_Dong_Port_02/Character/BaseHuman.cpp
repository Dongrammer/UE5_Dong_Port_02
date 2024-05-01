#include "Character/BaseHuman.h"

#include "Component/InventoryComponent.h"
#include "Component/WeaponComponent.h"
#include "Hero.h"
#include "Helper.h"

ABaseHuman::ABaseHuman()
{
	InventoryComponent = Helper::CreateActorComponent<UInventoryComponent>(this, "Inventory Component");
	WeaponComponent = Helper::CreateActorComponent<UWeaponComponent>(this, "Weapon Component");
}

void ABaseHuman::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseHuman::CreateCharacter()
{
	Super::CreateCharacter();
	// Mesh Setting
	GetMesh()->SetSkeletalMesh(Helper::GetAsset<USkeletalMesh>(L"/Game/Characters/Base/Mannequins/Meshes/SKM_Manny"));
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
}

void ABaseHuman::SetCharacterMovement()
{
	Super::SetCharacterMovement();
}

void ABaseHuman::GetItems(FItemData item, int count)
{
	InventoryComponent->GetItems(item, count);
}

bool ABaseHuman::CheckItemWeight(float itemweight)
{
	if (InventoryComponent->CheckWeight(itemweight))
		return true;
	else
	{
		// ���Ը� �ʰ��߽��ϴ� ���
		return false;
	}
}

bool ABaseHuman::GetWeaponHolding()
{
	return WeaponComponent->GetWeaponHolding();
}
