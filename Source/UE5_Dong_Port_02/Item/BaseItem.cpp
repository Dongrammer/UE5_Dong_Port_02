#include "Item/BaseItem.h"

#include "Components/SphereComponent.h"
#include "Components/TextRenderComponent.h"
#include "Character/BaseHuman.h"
#include "Character/Hero.h"
#include "Helper.h"

DEFINE_LOG_CATEGORY(ItemLog);

/* 
	[Static Mesh], [ItemID], [Collision ������], [Text ��ġ] ���� ����,  
*/

ABaseItem::ABaseItem()
{
 	PrimaryActorTick.bCanEverTick = true;

	itemdata.ItemType = EItemType::E_None;
	Rarity = ERarity::E_None;

	Scene = Helper::CreateSceneComponent<USceneComponent>(this, "Scene");
	SphereComponent = Helper::CreateSceneComponent<USphereComponent>(this, "Sphere Component", Scene);
	StaticMesh = Helper::CreateSceneComponent<UStaticMeshComponent>(this, "Static Mesh", Scene);
	Text = Helper::CreateSceneComponent<UTextRenderComponent>(this, "Interaction Text", Scene);

	TextSetting();
}

void ABaseItem::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseItem::DataTableSetting()
{
	if (itemdata.ItemID == "")
	{
		UE_LOG(ItemLog, Warning, TEXT("%s : ItemID is NULL"), *this->GetName());
	}
}

void ABaseItem::TextSetting()
{
	Text->SetText(FText::FromString("Get [E]"));
	Text->SetHiddenInGame(true);
	Text->SetTextRenderColor(FColor::Black);
	Text->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	Text->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextBottom);
}

void ABaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!Text->bHiddenInGame && AccessPlayer)
	{
		// Interaction Text Setting
		if (Cast<AHero>(AccessPlayer))
		{
			FRotator Rotator = AccessPlayer->GetControlRotation() + FRotator(0, 0, -180);
			Text->SetRelativeRotation(Rotator);
		}

		if (AccessPlayer->bInteraction)
		{
			UE_LOG(ItemLog, Log, TEXT("!!!"));
			if (AccessPlayer->CheckItemWeight(Weight))
			{
				AccessPlayer->GetItems(this->itemdata, 1);
				Destroy();
			}

			return;
		}
	}
}

void ABaseItem::TextOnOff()
{
	Text->SetHiddenInGame(!Text->bHiddenInGame);
}

