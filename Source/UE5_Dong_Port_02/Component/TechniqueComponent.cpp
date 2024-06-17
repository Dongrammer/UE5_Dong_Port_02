#include "Component/TechniqueComponent.h"

#include "../Character/Hero.h"
#include "Component/ActionComponent.h"

#include "Technique/TechniqueHUDDataAsset.h"
#include "Widget/Technique/TechniqueHUD.h"

#include "Widget/Technique/TechniqueNode.h"
#include "Widget/Technique/TechniqueSelectNodeSpace.h"

#include "Components/Button.h"

#include "Helper.h"

DEFINE_LOG_CATEGORY(TechniqueComponentLog);

UTechniqueComponent::UTechniqueComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	TechniqueHUDDataAsset = Helper::GetAsset<UTechniqueHUDDataAsset>(L"/Game/Widget/Technique/DA_TechniqueHUD");

	// ActionData Init
	FActionData TempData;
	TempData.ActionNumber = 0;
	TempData.ActionType = EActionType::E_None;
	SelectedAction.Init(TempData, 5);
}

void UTechniqueComponent::ToggleHUD()
{
	// Safe Check
	for (int i = static_cast<uint8>(EWeaponType::E_None) + 1; i < static_cast<uint8>(EWeaponType::E_Max); i++)
	{
		EWeaponType type = static_cast<EWeaponType>(i);
		if (!HUDs.FindRef(type)) return;
	}

	for (int i = static_cast<uint8>(EWeaponType::E_None) + 1; i < static_cast<uint8>(EWeaponType::E_Max); i++)
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
				Player->SetMouseCenter();
			}
		}
		else
		{
			hud->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UTechniqueComponent::NodeHUDNodeClick(UTechniqueNode* node)
{
	if (CurrentTP - node->RequiredTP < 0) return;

	if (SelectedNode != node)
	{
		NodeSelected(node);
		return;
	}

	// Active Node First Learn
	if (node->GetActive() == true && node->GetNodeLevel() == 0)
	{
		AvailableAction.Add(node->GetAction());
		node->ActiveNode();

		node->AddNodeLevel();
		CurrentHUD->SelectHUD->AddNode(node);
	}
	else if (node->GetNodeLevel() >= node->GetMaxNodeLevel()) return;

	// Passive Node
	if (node->GetActive() == false)
	{
		if (node->GetNodeLevel() == 0) node->ActiveNode();

		node->AddNodeLevel();
		Player->GetActionComponent()->PassiveLevelUp(node->ActionData, node->GetPassiveType());
	}

	// Set TP
	CurrentTP -= node->RequiredTP;
	for (int i = static_cast<uint8>(EWeaponType::E_None) + 1; i < static_cast<uint8>(EWeaponType::E_Max); i++)
	{
		EWeaponType type = static_cast<EWeaponType>(i);
		HUDs.FindRef(type)->SettingTP(CurrentTP, MaxTP);
	}

	// Require Node Check

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
	for (int i = static_cast<uint8>(EWeaponType::E_None) + 1; i < static_cast<uint8>(EWeaponType::E_Max); i++)
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

		// Node Connect
		for (TObjectPtr<UTechniqueNode> Node : HUD->NodeHUD->Nodes)
		{
			Node->NodeLevelSetting();
			Node->ConnectRequireNode();
			Node->DNodeSelect.AddUFunction(this, "NodeHUDNodeClick");
		}

		// Select NodeSpace Connect
		for (int j = 0; j < HUD->SelectHUD->NodeSpaces.Num(); j++)
		{
			HUD->SelectHUD->NodeSpaces[j]->DSelectAction.AddUFunction(this, "SelectHUDNodeClick");
		}

		// DashNodeHUD
		TArray<EDashAction> dashes;
		switch (type)
		{
		case EWeaponType::E_Gauntlet:
		{
			for (int j = static_cast<uint8>(EDashAction::E_GA_Dash_Start) + 1; j < static_cast<uint8>(EDashAction::E_GA_Dash_End); j++)
			{
				dashes.Add(static_cast<EDashAction>(j));
			}
			break;
		}
		case EWeaponType::E_Sword:
		{
			for (int j = static_cast<uint8>(EDashAction::E_SW_Dash_Start) + 1; j < static_cast<uint8>(EDashAction::E_SW_Dash_End); j++)
			{
				dashes.Add(static_cast<EDashAction>(j));
			}
			break;
		}
		}
		HUD->DashHUD->InitHUD(dashes);
		HUD->DashHUD->DSelectNode.AddUFunction(this, "SelectDashAction");

		FScriptDelegate dashinfoclicked;
		dashinfoclicked.BindUFunction(this, "SetInfoDashNode");
		HUD->DashHUD->BT_Info->OnClicked.Add(dashinfoclicked);

		//Player->GetActionComponent()->SettingDashAction(dashes[0]); 나중에 무기 종류별 생기면 변경
		
		HUDs.Add(type, HUD);
	}


	Player->GetActionComponent()->SettingDashAction(EDashAction::E_GA_Dash_01);
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

void UTechniqueComponent::SetInfoDashNode()
{
	if (SelectedNode)
	{
		SelectedNode->SelectedIMVisible(false);
		SelectedNode->bNodeSelected = false;
		SelectedNode = nullptr;
	}

	CurrentHUD->DashHUD->ClickImageVisible(true);

	FNodeInfoData data;
	data = CurrentHUD->DashHUD->GetNodeInfoData();

	CurrentHUD->InfoHUD->InfoSetting(data);
}

void UTechniqueComponent::NodeSelected(UTechniqueNode* node)
{
	CurrentHUD->DashHUD->ClickImageVisible(false);

	if (SelectedNode)
	{
		SelectedNode->SelectedIMVisible(false);
		SelectedNode->bNodeSelected = false;
	}
	
	SelectedNode = node;
	SelectedNode->bNodeSelected = true;
	SelectedNode->SelectedIMVisible(true);

	FNodeInfoData data;
	data.NodeDescription = SelectedNode->NodeDescription;
	data.NodeName = SelectedNode->NodeName;
	data.RequireTP = SelectedNode->RequiredTP;

	CurrentHUD->InfoHUD->InfoSetting(data);
}

void UTechniqueComponent::SelectDashAction(EDashAction dash)
{
	// Check Safe
	if (dash == EDashAction::E_None)
	{
		UE_LOG(TechniqueComponentLog, Warning, TEXT("SelectDashAction : DashAction Is NULL !!"));
		return;
	}

	Player->GetActionComponent()->SettingDashAction(dash);
}

void UTechniqueComponent::SelectHUDNodeClick(FActionData action, uint8 spaceNum)
{
	SelectedAction[spaceNum] = action;
	Player->GetActionComponent()->SettingActions(SelectedAction);
}

