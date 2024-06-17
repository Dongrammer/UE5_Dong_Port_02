#include "Component/EquipComponent.h"

#include "Character/BaseHuman.h"
#include "Character/Hero.h"
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

void UEquipComponent::Equip()
{
}

