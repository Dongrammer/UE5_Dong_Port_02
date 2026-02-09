#include "Widget/Technique/TechniqueNode.h"

#include "Components/SizeBox.h"
#include "Components/VerticalBox.h"
#include "Components/Overlay.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Technique/TechniqueNodeBase.h"

#include "Character/Hero.h"

UTechniqueNodeBase* UTechniqueNode::GetTechNode()
{
	if (TechNode) return TechNode;

	return nullptr;
}

void UTechniqueNode::NodeInit()
{
	hero = Cast<AHero>(GetOwningPlayerPawn());
	if (!hero)
	{
		UE_LOG(LogTemp, Warning, TEXT("TechniqueNode : Hero Is NULL !!"));
	}

	if (!TechNode) return;

	NodeRefresh(0);

	// NodeSetting
	Tx_NodeName->SetText(FText::FromName(TechNode->NodeName));
}

void UTechniqueNode::NodeRefresh(uint8 curLevel)
{
	//UE_LOG(LogTemp, Warning, TEXT("Refresh Node: %s"), *GetName());
	NodeLevelSetting(curLevel);
	/*if (DConnectRequireNode.IsBound())
	{
		UE_LOG(LogTemp, Warning, TEXT("NodeRefresh IsBound : %d"), curLevel);
		DConnectRequireNode.Broadcast(this);
	}*/
}
//
//void UTechniqueNode::CheckRequirements()
//{
//	FRequirements req = TechNode->Requirements;
//	
//	if (req.RequireNode == nullptr)
//	{
//		Unlock();
//		return;
//	}
//
//	if (req.RequireCharacterLevel > hero->GetCharacterLevel()) return;
//	if (req.RequireNodeLevel > req.RequireNode->CurNodeLevel) return;
//
//	Unlock();
//}

void UTechniqueNode::Unlock()
{
	if (bUnlock) return;

	bUnlock = true;
	IM_Lock->SetVisibility(ESlateVisibility::Hidden);
}

void UTechniqueNode::NativeConstruct()
{
	Super::NativeConstruct();

	FScriptDelegate Main_Clicked;
	Main_Clicked.BindUFunction(this, "Bt_Main_Clicked");

	Bt_Main->OnClicked.AddUnique(Main_Clicked);

	FLinearColor color = Im_Base->GetColorAndOpacity();
	color.R = 0.2f;
	color.G = 0.2f;
	color.B = 0.2f;

	Im_Base->SetColorAndOpacity(color);
	IM_Selected->SetVisibility(ESlateVisibility::Hidden);
}

void UTechniqueNode::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (TechNode)
	{
		const TObjectPtr<UTechniqueNodeBase> Node = TechNode.Get();
		Tx_NodeName->SetText(FText::FromName(Node->NodeName));
		Im_Base->SetBrushFromTexture(Node->Icon);
	}
}

void UTechniqueNode::Bt_Main_Clicked()
{
	if (bUnlock == false) return;
	// 잠겨있습니다! widget띄우기

	if (DNodeSelect.IsBound())
	{
		DNodeSelect.Broadcast(this);
	}
}

void UTechniqueNode::ActiveNode()
{
	FLinearColor color = Im_Base->GetColorAndOpacity();
	color.R = 1.0f;
	color.G = 1.0f;
	color.B = 1.0f;

	Im_Base->SetColorAndOpacity(color);
}
//
//void UTechniqueNode::AddNodeLevel()
//{
//	if (!TechNode) return;
//
//	NodeRefresh();
//}

void UTechniqueNode::NodeLevelSetting(uint8 curLevel)
{
	if (!TechNode) return;

	uint8 CurNodeLevel = curLevel;
	uint8 MaxNodeLevel = TechNode->MaxNodeLevel;

	Tx_Level->SetText(FText::FromString(FString::Printf(TEXT("( %d / %d )"), CurNodeLevel, MaxNodeLevel)));
}

void UTechniqueNode::SelectedIMVisible(bool visible)
{
	if (visible)
		IM_Selected->SetVisibility(ESlateVisibility::Visible);
	else 
		IM_Selected->SetVisibility(ESlateVisibility::Hidden);
}
