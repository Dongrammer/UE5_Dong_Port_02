#include "Component/TechniqueComponent.h"

#include "../Character/Hero.h"
#include "Component/ActionComponent.h"

#include "Technique/TechniqueHUDDataAsset.h"
#include "Widget/Technique/TechniqueHUD.h"

#include "Action/BaseAction.h"

#include "Helper.h"

DEFINE_LOG_CATEGORY(TechniqueComponentLog);

UTechniqueComponent::UTechniqueComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	//TechniqueHUDDataAsset = Cast<UTechniqueHUDDataAsset>(Helper::GetAsset<UDataAsset>(L"/Game/Widget/Technique/DA_TechniqueHUD"));
	TechniqueHUDDataAsset = Helper::GetAsset<UTechniqueHUDDataAsset>(L"/Game/Widget/Technique/DA_TechniqueHUD");
}

void UTechniqueComponent::ToggleHUD()
{
	if (Gauntlet_TechniqueHUD->IsVisible() || Sword_TechniqueHUD->IsVisible())
	{
		Gauntlet_TechniqueHUD->SetVisibility(ESlateVisibility::Hidden);
		Player->SetMouseState(false, EInputModeType::E_GameOnly);
	}
	else
	{
		switch (CurrentWeaponType)
		{
		case EWeaponType::E_Sword:
		{
			Sword_TechniqueHUD->SetVisibility(ESlateVisibility::Visible);
			Player->SetMouseState(true, EInputModeType::E_GameAndUIOnly, Sword_TechniqueHUD);
			break;
		}
		default:
		{
			Gauntlet_TechniqueHUD->SetVisibility(ESlateVisibility::Visible);
			Player->SetMouseState(true, EInputModeType::E_GameAndUIOnly, Gauntlet_TechniqueHUD);
			break;
		}
		}
	}
}

void UTechniqueComponent::ApplyAction()
{
	Player->GetActionComponent()->SettingActions(SelectedAction);
}

void UTechniqueComponent::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<AHero>(GetOwner());
	PlayerController = Cast<APlayerController>(GetOwner()->GetOwner());

	if (!TechniqueHUDDataAsset)
	{
		UE_LOG(TechniqueComponentLog, Warning, TEXT("TechniqueHUDDataAsset Is NULL !!"));
		return;
	}

	Sword_TechniqueHUD = CreateWidget<UTechniqueHUD>(PlayerController, TechniqueHUDDataAsset->SwordHUD, "Sword Technique HUD");
	Sword_TechniqueHUD->AddToViewport();
	Sword_TechniqueHUD->SetVisibility(ESlateVisibility::Hidden);
	Gauntlet_TechniqueHUD = CreateWidget<UTechniqueHUD>(PlayerController, TechniqueHUDDataAsset->GauntletHUD, "Gauntlet Technique HUD");
	Gauntlet_TechniqueHUD->AddToViewport();
	Gauntlet_TechniqueHUD->SetVisibility(ESlateVisibility::Hidden);

	Sword_TechniqueHUD->NextHUD = Gauntlet_TechniqueHUD;
	Sword_TechniqueHUD->PrevHUD = Gauntlet_TechniqueHUD;
	Gauntlet_TechniqueHUD->NextHUD = Sword_TechniqueHUD;
	Gauntlet_TechniqueHUD->PrevHUD = Sword_TechniqueHUD;

}

void UTechniqueComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

