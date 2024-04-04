#include "Character/BaseHuman.h"

#include "Component/InventoryComponent.h"
#include "Item/BaseItem.h"
#include "Helper.h"

ABaseHuman::ABaseHuman()
{
	InventoryComponent = Helper::CreateActorComponent<UInventoryComponent>(this, "Inventory Component");
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

void ABaseHuman::GetItems(ABaseItem* item, int count)
{
	InventoryComponent->GetItems(item, count);
}

bool ABaseHuman::CheckItemWeight(float itemweight)
{
	if (InventoryComponent->CheckWeight(itemweight))
		return true;
	else
	{
		// 무게를 초과했습니다 출력
		return false;
	}
}
