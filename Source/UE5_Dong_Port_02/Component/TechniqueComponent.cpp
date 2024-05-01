#include "Component/TechniqueComponent.h"

#include "../Character/Hero.h"
#include "Component/ActionComponent.h"

#include "Technique/TechniqueHUDDataAsset.h"
#include "Widget/Technique/TechniqueHUD.h"

#include "Widget/Technique/TechniqueNode.h"
#include "Widget/Technique/TechniqueSelectNodeSpace.h"

#include "Components/Button.h"

#include "Action/BaseAction.h"

#include "Helper.h"

DEFINE_LOG_CATEGORY(TechniqueComponentLog);

UTechniqueComponent::UTechniqueComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	TechniqueHUDDataAsset = Helper::GetAsset<UTechniqueHUDDataAsset>(L"/Game/Widget/Technique/DA_TechniqueHUD");

	SelectedAction.Init(nullptr, 5);
}

void UTechniqueComponent::ToggleHUD()
{
	// Safe Check
	for (int i = static_cast<int>(EWeaponType::E_None) + 1; i < static_cast<int>(EWeaponType::E_Max); i++)
	{
		EWeaponType type = static_cast<EWeaponType>(i);
		if (!HUDs.FindRef(type)) return;
	}

	for (int i = static_cast<int>(EWeaponType::E_None) + 1; i < static_cast<int>(EWeaponType::E_Max); i++)
	{
		EWeaponType type = static_cast<EWeaponType>(i);
		TObjectPtr<UTechniqueHUD> hud = HUDs.FindRef(type);

		if (CurrentHUD->HUDWeaponType == type)
		{
			if (CurrentHUD->IsVisible())
			{
				CurrentHUD->SetVisibility(ESlateVisibility::Hidden);
				Player->SetMouseState(false, EInputModeType::E_GameOnly);
			}
			else
			{
				CurrentHUD->SetVisibility(ESlateVisibility::Visible);
				Player->SetMouseState(true, EInputModeType::E_GameAndUIOnly, CurrentHUD);
			}
		}
		else
		{
			hud->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UTechniqueComponent::SelectNode(UTechniqueNode* node)
{
	if (CurrentTP - node->RequiredTP < 0) return;

	if (node->GetActionLevel() == 0)
	{
		AvailableAction.Add(node->GetAction());
		node->ActiveNode();

		CurrentHUD->SelectHUD->AddNode(node);
	}
	else if (node->GetActionLevel() >= node->GetMaxActionLevel()) return;

	node->AddActionLevel();

	// Set TP
	CurrentTP -= node->RequiredTP;
	for (int i = static_cast<int>(EWeaponType::E_None) + 1; i < static_cast<int>(EWeaponType::E_Max); i++)
	{
		EWeaponType type = static_cast<EWeaponType>(i);
		HUDs.FindRef(type)->SettingTP(CurrentTP, MaxTP);
	}

}

void UTechniqueComponent::BeginPlay()
{
	Super::BeginPlay();

	// Set Owner
	Player = Cast<AHero>(GetOwner());
	PlayerController = Cast<APlayerController>(GetOwner()->GetOwner());

	// Safe Check
	if (!TechniqueHUDDataAsset)
	{
		UE_LOG(TechniqueComponentLog, Warning, TEXT("TechniqueHUDDataAsset Is NULL !!"));
		return;
	}
	if (!PlayerController)
	{
		UE_LOG(TechniqueComponentLog, Warning, TEXT("PlayerController Is NULL !!"));
		return;
	}

	// Create Widget
	for (int i = static_cast<int>(EWeaponType::E_None) + 1; i < static_cast<int>(EWeaponType::E_Max); i++)
	{
		EWeaponType type = static_cast<EWeaponType>(i);
		TSubclassOf<UTechniqueHUD> HUDClass = TechniqueHUDDataAsset->HUDs.FindRef(type);
		TObjectPtr<UTechniqueHUD> HUD = CreateWidget<UTechniqueHUD>(PlayerController, HUDClass);
		HUD->AddToViewport();
		HUD->SetVisibility(ESlateVisibility::Hidden);
		HUD->SettingTP(CurrentTP, MaxTP);
		HUD->SetWeaponType(type);

		FScriptDelegate NextHUDPressed, PrevHUDPressed;
		NextHUDPressed.BindUFunction(this, "MoveToNextHUD");
		PrevHUDPressed.BindUFunction(this, "MoveToPrevHUD");
		HUD->Bt_NextHUD->OnClicked.Add(NextHUDPressed);
		HUD->Bt_PrevHUD->OnClicked.Add(PrevHUDPressed);

		for (int j = 0; j < HUD->SelectHUD->NodeSpaces.Num(); j++)
		{
			HUD->SelectHUD->NodeSpaces[j]->DSelectAction.AddUFunction(this, "SelectActionNode");
		}

		HUDs.Add(type, HUD);
	}

	// Node Connect
	for (int i = static_cast<int>(EWeaponType::E_None) + 1; i < static_cast<int>(EWeaponType::E_Max); i++)
	{
		EWeaponType type = static_cast<EWeaponType>(i);

		for (TObjectPtr<UTechniqueNode> Node : HUDs.FindRef(type)->NodeHUD->Nodes)
		{
			Node->DNodeSelect.AddUFunction(this, "SelectNode");
			Node->ActionLevelSetting();
		}
	}

	// Basic CurrentHUD Setting
	CurrentHUD = HUDs.FindRef(EWeaponType::E_Gauntlet);

	
}

void UTechniqueComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTechniqueComponent::MoveToNextHUD()
{
	EWeaponType temp = static_cast<EWeaponType>(static_cast<int>(CurrentHUD->HUDWeaponType) + 1);

	if (temp == EWeaponType::E_Max) temp = static_cast<EWeaponType>(static_cast<int>(EWeaponType::E_None) + 1);

	CurrentHUD = HUDs.FindRef(temp);

	ToggleHUD();
}

void UTechniqueComponent::MoveToPrevHUD()
{
	EWeaponType temp = static_cast<EWeaponType>(static_cast<int>(CurrentHUD->HUDWeaponType) - 1);

	if (temp == EWeaponType::E_None) temp = static_cast<EWeaponType>(static_cast<int>(EWeaponType::E_Max) - 1);

	CurrentHUD = HUDs.FindRef(temp);

	ToggleHUD();
}

void UTechniqueComponent::SelectActionNode(TSubclassOf<ABaseAction> action, uint8 spaceNum)
{
	SelectedAction[spaceNum] = action;
	Player->GetActionComponent()->SettingActions(SelectedAction);
}

