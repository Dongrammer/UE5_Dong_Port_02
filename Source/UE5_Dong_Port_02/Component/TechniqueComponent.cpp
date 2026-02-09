#include "Component/TechniqueComponent.h"

#include "../Character/Hero.h"
#include "Component/ActionComponent.h"

#include "Technique/TechniqueHUDDataAsset.h"
#include "Widget/Technique/TechniqueHUD.h"
#include "Action/ActionData.h"

#include "Widget/Technique/TechniqueNode.h"
#include "Technique/TechniqueNodeActive.h"
#include "Technique/TechniqueNodePassive.h"
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
	FActionDataArray TempArray;
	TempData.ActionNumber = 0;
	TempData.WeaponType = EWeaponType::E_None;
	TempArray.ActionDatas.Init(TempData, 5);
	for (int i = static_cast<uint8>(EWeaponType::E_None) + 1; i < static_cast<uint8>(EWeaponType::E_Max); i++)
	{
		SelectedAction.Add(static_cast<EWeaponType>(i), TempArray);
	}
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

bool UTechniqueComponent::GetHUDVisible()
{
	return CurrentHUD->IsVisible();
}

void UTechniqueComponent::NodeHUDNodeClick(UTechniqueNode* node)
{
	if (!node || !node->TechNode) return;

	UTechniqueNodeBase* Tech = node->TechNode;

	if (CurrentTP - Tech->RequireTP < 0) return;
	if (SelectedNode != node)
	{
		NodeSelected(node);
		return;
	}
	// Finding RuntimeNodes
	bool bnew = true;
	if (!RuntimeNodes.Contains(Tech))
	{
		RuntimeNodes.Add(Tech, FRuntimeTechNodeData{});
	}

	if (RuntimeNodes.Contains(Tech))
	{
		FRuntimeTechNodeData& RNodeData = RuntimeNodes[Tech];
		if (Tech->MaxNodeLevel <= RNodeData.CurNodeLevel) return;
		if (RNodeData.CurNodeLevel == 0) node->ActiveNode();

		// Active
		if (auto* active = Cast<UTechniqueNodeActive>(Tech))
		{
			if (RNodeData.CurNodeLevel == 0) // Active Node First Learn
			{
				AvailableAction.Add(active->GetAction());
				CurrentHUD->SelectHUD->AddNode(active);
			}
		}
		// Passive
		if (auto* passive = Cast<UTechniqueNodePassive>(Tech))
		{
			Player->GetActionComponent()->PassiveLevelUp(passive->TargetAction, passive->PassiveType);
		}
		// Level Up
		RNodeData.CurNodeLevel++;
		node->NodeRefresh(RNodeData.CurNodeLevel);
		if (const auto& dependents = NodeDependents.Find(Tech))
		{
			for (auto& req : *dependents)
			{
				CheckRequirements(req);
			}
		}

		// Set TP
		CurrentTP -= Tech->RequireTP;
		for (int i = static_cast<uint8>(EWeaponType::E_None) + 1; i < static_cast<uint8>(EWeaponType::E_Max); i++)
		{
			EWeaponType type = static_cast<EWeaponType>(i);
			HUDs.FindRef(type)->SettingTP(CurrentTP, MaxTP);
		}
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
		for (UTechniqueNode* Node : HUD->NodeHUD->Nodes)
		{
			Node->NodeInit();
			Node->DNodeSelect.AddUObject(this, &UTechniqueComponent::NodeHUDNodeClick);

			if (!Node->TechNode) continue;
			NodeWidgetMap.Add(Node->TechNode, Node);

			for (auto& req : Node->TechNode->Requirements.RequireNode)
			{
				UE_LOG(LogTemp, Warning, TEXT("!!"));
				NodeDependents.FindOrAdd(req.Key).Add(Node->TechNode);
			}
			CheckRequirements(Node->TechNode);

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
		case EWeaponType::E_OneHandSword:
		{
			for (int j = static_cast<uint8>(EDashAction::E_OHSW_Dash_Start) + 1; j < static_cast<uint8>(EDashAction::E_OHSW_Dash_End); j++)
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

	UTechniqueNodeBase* tn = node->GetTechNode();
	FNodeInfoData data;
	data.NodeDescription = FText::FromName(tn->NodeDescription);
	data.NodeName = FText::FromName(tn->NodeName);
	data.RequireTP = tn->RequireTP;

	CurrentHUD->InfoHUD->InfoSetting(data);
}

void UTechniqueComponent::CheckRequirements(UTechniqueNodeBase* CheckNode)
{
	const FRequirements& Req = CheckNode->Requirements;
	bool bUnlock = true;

	// CharacterLevel
	if (Player->GetCharacterLevel() < Req.RequireCharacterLevel) bUnlock = false;

	// Prievious Node
	for (auto& ReqNode : Req.RequireNode)
	{
		const UTechniqueNodeBase* RequireNode = ReqNode.Key;
		const uint8 RequireNodeLevel = ReqNode.Value;

		const FRuntimeTechNodeData* Runtime = RuntimeNodes.Find(RequireNode);

		if (!Runtime || Runtime->CurNodeLevel < RequireNodeLevel)
		{
			bUnlock = false;
			break;
		}
	}

	if (!bUnlock) return;

	if (UTechniqueNode* widget = NodeWidgetMap.FindRef(CheckNode))
		widget->Unlock();
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
	SelectedAction.Find(action.WeaponType)->ActionDatas[spaceNum] = action;
	Player->GetActionComponent()->SettingActions(SelectedAction.FindRef(action.WeaponType).ActionDatas);
}

