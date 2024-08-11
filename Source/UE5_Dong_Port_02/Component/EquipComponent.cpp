#include "Component/EquipComponent.h"

#include "TPS_GameInstance.h"
#include "Component/ItemComponent.h"
#include "Character/BaseHuman.h"
#include "Character/Hero.h"
#include "Item/BaseEquip.h"
#include "Widget/Equipment/EquipmentHUD.h"

DEFINE_LOG_CATEGORY(EquipComponentLog);

UEquipComponent::UEquipComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	OwnerCharacter = Cast<ABaseHuman>(GetOwner());

	InitEquipParts();
}

void UEquipComponent::BeginPlay()
{
	Super::BeginPlay();

	// ItemComponent Setting
	{
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
	}

	
	// 
}

void UEquipComponent::InitEquipParts()
{
	FItemData data;
	data.ItemID = FName("");
	data.ItemType = EItemType::E_None;

	for (int i = 1; i < static_cast<int>(EEquipType::E_Max); i++)
	{
		EEquipType type = static_cast<EEquipType>(i);
		EquipParts.Add(type, data);
		EquipmentParts.Add(type, nullptr);
	}
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
	EEquipType EquipType = ItemComponent->GetEquipType(item);
	
	if (EquipParts.FindRef(EquipType).ItemType != EItemType::E_None)
	{
		UnEquip(EquipType);
	}

	EquipParts.Find(EquipType)->ItemID = item.ItemID;
	EquipParts.Find(EquipType)->ItemType = item.ItemType;
	SpawnAndAttach(EquipType);
	/*
	switch (EquipType)
	{
	case EEquipType::E_Head:
	{
		// 이미 장착중인 장비가 있다면
		if (Head.ItemType != EItemType::E_None)
		{
			OwnerCharacter->GetItems(Head, 1);
			UnEquip(EquipType);
		}

		Head = item;
		SpawnAndAttach(EEquipType::E_Head);
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
	*/
	OwnerCharacter->EQuipItemStatus(ItemComponent->GetEquipmentDataTable(item).EquipStatus);


	if (EquipmentHUD)
	{
		HUDImageSetting(EquipType);
	}
}

void UEquipComponent::UnEquip(EEquipType type)
{
	/*FItemData data;
	data.ItemID = FName("");
	data.ItemType = EItemType::E_None;*/
	OwnerCharacter->GetItems(EquipParts.FindRef(type), 1);
	OwnerCharacter->UnequipItemStatus(ItemComponent->GetEquipmentDataTable(EquipParts.FindRef(type)).EquipStatus);
	EquipParts.Find(type)->ItemID = FName("");
	EquipParts.Find(type)->ItemType = EItemType::E_None;

	if (EquipmentParts.Contains(type)) EquipmentParts[type]->Destroy();
	
	/*
	switch (type)
	{
	case EEquipType::E_Head:
	{
		OwnerCharacter->UnequipItemStatus(ItemComponent->GetEquipmentDataTable(Head).EquipStatus);
		Head = data;

		if (HeadEquipment)
		{
			HeadEquipment->Destroy();
		}
		break;
	}
	case EEquipType::E_Chest:
	{
		Chest = data;
		break;
	}
	case EEquipType::E_Legs:
	{
		Legs = data;
		break;
	}
	case EEquipType::E_Feet:
	{
		Feet = data;
		break;
	}
	case EEquipType::E_Hands:
	{
		Hands = data;
		break;
	}
	case EEquipType::E_Weapon:
	{
		Weapon = data;
		break;
	}
	}
	*/
	if (EquipmentHUD)
	{
		HUDImageSetting(type);
	}
}

void UEquipComponent::SpawnAndAttach(EEquipType type)
{
	TSubclassOf<ABaseItem> ItemClass = ItemComponent->GetEquipItemClass(EquipParts.FindRef(type));
	FActorSpawnParameters SpawnParameter;
	SpawnParameter.Owner = OwnerCharacter;

	if (!ItemClass)
	{
		UE_LOG(EquipComponentLog, Warning, TEXT("SpawnAndAttach : ItemClass Is NULL !!"));
		return;
	}

	TObjectPtr<ABaseEquip> EquipItem = Cast<ABaseEquip>(GetWorld()->SpawnActor<AActor>(ItemClass, FVector(), FRotator(), SpawnParameter));
	if (!EquipmentParts.Contains(type))
	{
		UE_LOG(EquipComponentLog, Warning, TEXT("SpawnAndAttach: EquipmentParts Not Contained the type"));
		return;
	}
	if (!EquipItem)
	{
		UE_LOG(EquipComponentLog, Warning, TEXT("SpawnAndAttach: EquipItem Is NULL !!"));
		return;
	}

	EquipmentParts[type] = EquipItem;

	if (!EquipmentParts.FindRef(type))
	{
		UE_LOG(EquipComponentLog, Warning, TEXT("SpawnAndAttach : EquipmentParts Creating Error !!"));
		return;
	}

	EquipmentParts[type]->SetEquipment();
	
	// SetSocketName
	FName SocketName;
	switch (type)
	{
	case EEquipType::E_Head:
	{
		SocketName = "Helmet";
		break;
	}
	case EEquipType::E_Chest:
	{
		SocketName = "Chest";
		break;
	}
	case EEquipType::E_Legs:
	{
		SocketName = "Legs";
		break;
	}
	case EEquipType::E_Feet:
	{
		SocketName = "Feet";
		break;
	}
	case EEquipType::E_Hands:
	{
		SocketName = "Hands";
		break;
	}
	case EEquipType::E_Weapon:
	{
		SocketName = "Weapon";
		break;
	}
	case EEquipType::E_SubWeapon:
	{
		SocketName = "SubWeapon";
		break;
	}
	default:
	{
		UE_LOG(EquipComponentLog, Warning, TEXT("SpawnAndAttach : ItemType Error !!"));
		return;
	}
	}
	EquipmentParts[type]->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, SocketName);

	/*
	switch (type)
	{
	case EEquipType::E_Head:
	{
		ItemClass = ItemComponent->GetEquipmentDataTable(Head).ItemClass;

		if (!ItemClass)
		{
			UE_LOG(EquipComponentLog, Warning, TEXT("SpawnAndAttach : ItemClass Is NULL !!"));
			return;
		}

		HeadEquipment = Cast<ABaseEquip>(GetWorld()->SpawnActor<AActor>(ItemClass, FVector(), FRotator(), SpawnParameter));		// 아이템 스폰
		HeadEquipment->SetEquipment();																							// 필드 아이템이 아닌 장착 아이템으로 설정
		HeadEquipment->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "Helmet");

		break;
	}
	case EEquipType::E_Chest:
	{
		ItemClass = ItemComponent->GetEquipmentDataTable(Chest).ItemClass;
		break;
	}
	case EEquipType::E_Legs:
	{
		ItemClass = ItemComponent->GetEquipmentDataTable(Legs).ItemClass;
		break;
	}
	case EEquipType::E_Feet:
	{
		ItemClass = ItemComponent->GetEquipmentDataTable(Feet).ItemClass;
		break;
	}
	case EEquipType::E_Hands:
	{
		ItemClass = ItemComponent->GetEquipmentDataTable(Hands).ItemClass;
		break;
	}
	case EEquipType::E_Weapon:
	{
		ItemClass = ItemComponent->GetEquipmentDataTable(Weapon).ItemClass;
		break;
	}
	default:
	{
		UE_LOG(EquipComponentLog, Warning, TEXT("SpawnAndAttach : ItemType Error !!"));
		return;
	}
	}
	*/
}

void UEquipComponent::HUDImageSetting(EEquipType type)
{
	FItemData data;

	data = EquipParts.FindRef(type);
	/*
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
	*/

	if (data.ItemType == EItemType::E_None)
	{
		EquipmentHUD->InitSlotImage(type);
	}
	else
	{
		UTexture2D* texture = ItemComponent->GetEquipmentDataTable(data).Texture;
		ERarity rarity = ItemComponent->GetEquipmentDataTable(data).Rarity;
		const FLinearColor* rarityColor = ItemComponent->GetRarityColor(rarity);
		EquipmentHUD->SetSlotImage(type, texture, rarityColor);
	}
}

