#include "Item/BaseItem.h"

#include "Components/SphereComponent.h"
#include "ItemEnum.h"
#include "Helper.h"

/* 
	[Static Mesh], [ItemID], [Collision] 사이즈 직접 지정,  
*/

ABaseItem::ABaseItem()
{
 	PrimaryActorTick.bCanEverTick = true;

	ItemType = EItemType::E_None;
	Rarity = ERarity::E_None;

	Scene = Helper::CreateSceneComponent<USceneComponent>(this, "Scene");
	SphereComponent = Helper::CreateSceneComponent<USphereComponent>(this, "Sphere Component", Scene);
	StaticMesh = Helper::CreateSceneComponent<UStaticMeshComponent>(this, "Static Mesh", Scene);
}

void ABaseItem::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseItem::DataTableSetting()
{
}

void ABaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

