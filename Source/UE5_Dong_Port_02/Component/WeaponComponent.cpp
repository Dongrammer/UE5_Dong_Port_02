#include "Component/WeaponComponent.h"
#include "Item/BaseWeapon.h"
#include "Component/ItemComponent.h"
#include "TPS_GameInstance.h"

DEFINE_LOG_CATEGORY(WeaponCompLog);

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	
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

