#include "Component/EquipComponent.h"

#include "TPS_GameInstance.h"
#include "Character/BaseHuman.h"
#include "Character/Hero.h"
#include "Component/ItemComponent.h"
#include "Widget/Equipment/EquipmentHUD.h"

DEFINE_LOG_CATEGORY(EquipComponentLog);

UEquipComponent::UEquipComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	OwnerCharacter = Cast<ABaseHuman>(GetOwner());


}

void UEquipComponent::BeginPlay()
{
	Super::BeginPlay();

	//ItemComponent = UItemComponent::GetInstance();
	UTPS_GameInstance* GameInstance = Cast<UTPS_GameInstance>(GetWorld()->GetGameInstance());
	if (!GameInstance)
	{
		UE_LOG(EquipComponentLog, Warning, TEXT("GameInstance Is NULL !!"));
		return;
	}

	ItemComponent = GameInstance->GetItemComponent();
	if (!ItemComponent)
	{
		UE_LOG(EquipComponentLog, Warning, TEXT("ItemComponent Is NULL !!"));
		return;
	}

	UE_LOG(EquipComponentLog, Log, TEXT("ItemInstance ID : %p"), ItemComponent);
}

void UEquipComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UEquipComponent::ToggleHUD()
{
	EquipmentHUD->ToggleHUD();
}

void UEquipComponent::InitEquipmentHUD(TObjectPtr<UEquipmentHUD> hud)
{
	EquipmentHUD = hud;
	EquipmentHUD->SetVisibility(ESlateVisibility::Hidden);
}

void UEquipComponent::Equip(FItemData item)
{
	EEquipType EquipType = ItemComponent->GetEquipmentDataTable(item).EquipType;
	switch (EquipType)
	{
	case EEquipType::E_Head:
	{
		Head = item;
		break;
	}
	case EEquipType::E_Chest:
	{
		Chest = item;
		break;
	}
	case EEquipType::E_Legs:
	{
		Legs = item;
		break;
	}
	case EEquipType::E_Feet:
	{
		Feet = item;
		break;
	}
	case EEquipType::E_Hands:
	{
		Hands = item;
		break;
	}
	case EEquipType::E_Weapon:
	{
		Weapon = item;
		break;
	}
	}

	if (EquipmentHUD)
	{
		HUDImageSetting(EquipType);
	}
}

void UEquipComponent::HUDImageSetting(EEquipType type)
{
	FItemData data;
	switch (type)
	{
	case EEquipType::E_Head:
	{
		data = Head;
		break;
	}
	case EEquipType::E_Chest:
	{
		data = Chest;
		break;
	}
	case EEquipType::E_Legs:
	{
		data = Legs;
		break;
	}
	case EEquipType::E_Feet:
	{
		data = Feet;
		break;
	}
	case EEquipType::E_Hands:
	{
		data = Hands;
		break;
	}
	case EEquipType::E_Weapon:
	{
		data = Weapon;
		break;
	}
	}

	UTexture2D* texture = ItemComponent->GetEquipmentDataTable(data).Texture;
	ERarity rarity = ItemComponent->GetEquipmentDataTable(data).Rarity;
	const FLinearColor* rarityColor = ItemComponent->GetRarityColor(rarity);
	if (rarity == ERarity::E_Common)
	{
		UE_LOG(LogTemp, Log, TEXT("Common"));
	}
	else if (rarity == ERarity::E_Rare)
	{
		UE_LOG(LogTemp, Log, TEXT("Rare"));
	}

	EquipmentHUD->SetSlotImage(type, texture, rarityColor);
}

