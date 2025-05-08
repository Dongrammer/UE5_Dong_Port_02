#include "Component/WeaponComponent.h"
#include "Item/BaseWeapon.h"
#include "Component/ItemComponent.h"
#include "TPS_GameInstance.h"
#include "Character/BaseHuman.h"
//#include "Components/CapsuleComponent.h"

DEFINE_LOG_CATEGORY(WeaponCompLog);

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Owner = Cast<ABaseHuman>(GetOwner());
	// ItemComponent Setting
	{
		UTPS_GameInstance* GameInstance = Cast<UTPS_GameInstance>(GetWorld()->GetGameInstance());
		if (!GameInstance)
		{
			UE_LOG(WeaponCompLog, Warning, TEXT("GameInstance Is NULL !!"));
			return;
		}

		ItemComponent = GameInstance->GetItemComponent();
		if (!ItemComponent)
		{
			UE_LOG(WeaponCompLog, Warning, TEXT("ItemComponent Is NULL !!"));
			return;
		}
	}
}

void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UWeaponComponent::SetCurrentWeapon(TObjectPtr<ABaseWeapon> weapon)
{
	CurrentWeapon = weapon;
	CurrentWeaponType = ItemComponent->GetWeaponType(weapon->itemdata);
}

void UWeaponComponent::WeaponHolding()
{
	EWeaponType type = CurrentWeapon->GetWeaponType();

	FName SocketName = TEXT("");
	switch (type)
	{
	case EWeaponType::E_OneHandSword:
	{
		SocketName = TEXT("OneHandSword_Handle");
		break;
	}
	default:
	{
		break;
	}
	}

	if (SocketName == TEXT(""))
	{
		UE_LOG(WeaponCompLog, Warning, TEXT("WeaponHolding : SocketName Error !!"));
		return;
	}

	CurrentWeapon->AttachToComponent(Owner->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, SocketName);
}

void UWeaponComponent::WeaponUnHolding()
{
	EWeaponType type = CurrentWeapon->GetWeaponType();

	FName SocketName = TEXT("");
	switch (type)
	{
	case EWeaponType::E_OneHandSword:
	{
		SocketName = TEXT("OneHandSword_Holder");
		break;
	}
	default:
	{
		break;
	}
	}

	if (SocketName == TEXT(""))
	{
		UE_LOG(WeaponCompLog, Warning, TEXT("WeaponHolding : SocketName Error !!"));
		return;
	}

	CurrentWeapon->AttachToComponent(Owner->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, SocketName);
}

TObjectPtr<UCapsuleComponent> UWeaponComponent::GetWeaponCapsule()
{
	return CurrentWeapon->GetWeaponCapsule();
}

