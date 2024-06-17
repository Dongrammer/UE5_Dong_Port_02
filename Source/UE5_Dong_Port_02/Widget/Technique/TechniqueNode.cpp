#include "Widget/Technique/TechniqueNode.h"

#include "Components/SizeBox.h"
#include "Components/Overlay.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UTechniqueNode::ConnectRequireNode()
{
	if (!RequireNode)
	{
		Unlock();
		return;
	}
	RequireNode->DNodeSelect.AddUFunction(this, "CheckRequireNode");
	/* 
		Technique Component�� Node�� AddNodeLevel���� ���� ����Ǵ� ����. ��������Ʈ�� ���ʺ��� ����ż� �׷���? 
		CheckRequireNode()�� ������ �ٲٰų�, TechniqueComponent���� ��������Ʈ�� ������ �ٲٰų� �ؾ���.
		������ ����� ������ ��������Ʈ�� ������ �ٲ��� ������, ���ڷ� ó��.
	*/
}

void UTechniqueNode::CheckRequireNode()
{
	if (!RequireNode) return;

	if (RequireNode->NodeLevel >= RequireNodeLevel - 1 && RequireNode->bNodeSelected)
	{
		Unlock();
	}
}

void UTechniqueNode::Unlock()
{
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

void UTechniqueNode::Bt_Main_Clicked()
{
	if (bUnlock == false) return;
	// ����ֽ��ϴ�! widget����

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

void UTechniqueNode::AddNodeLevel()
{
	NodeLevel++;
	NodeLevelSetting();
}

void UTechniqueNode::NodeLevelSetting()
{
	Tx_Level->SetText(FText::FromString(FString::Printf(TEXT("( %d / %d )"), NodeLevel, MaxNodeLevel)));
}

void UTechniqueNode::SelectedIMVisible(bool visible)
{
	if (visible)
		IM_Selected->SetVisibility(ESlateVisibility::Visible);
	else 
		IM_Selected->SetVisibility(ESlateVisibility::Hidden);
}
