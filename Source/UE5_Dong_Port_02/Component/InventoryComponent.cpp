#include "Component/InventoryComponent.h"

#include "Character/BaseCharacter.h"
#include "../Public/Blueprint/UserWidget.h"
#include "../Widget/Inventory/InventoryHUD.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// HUD
	InvenHUDClass = nullptr;
	InvenHUD = nullptr;
	
}


void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ABaseCharacter>(GetOwner());
	OwnerController = Cast<APlayerController>(Owner->GetOwner());
	
	if (OwnerController && InvenHUDClass)
	{
		InvenHUD = CreateWidget<UInventoryHUD>(OwnerController, InvenHUDClass, "Inventory HUD");
		InvenHUD->AddToViewport();
	}
}

void UInventoryComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (InvenHUD)
	{
		InvenHUD->RemoveFromParent();
		InvenHUD = nullptr;
	}

	Super::EndPlay(EndPlayReason);
}


void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

