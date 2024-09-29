#include "Widget/InteractionHUD.h"

#include "Components/CanvasPanel.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/WidgetSwitcher.h"

//void UInteractionHUD::SetName(FName name)
//{
//	if (name == "")
//	{
//		TB_Name->SetText(FText::FromString("???"));
//		return;
//	}
//
//	TB_Name->SetText(FText::FromName(name));
//}

void UInteractionHUD::SetPosition(FVector2D position)
{
	SB_Body->SetRenderTranslation(position);
}

void UInteractionHUD::ActiveWidget(EInteractionHUDType type, FName name)
{
	if (name == "")
	{
		TB_Name->SetText(FText::FromString("???"));
	}
	else
	{
		TB_Name->SetText(FText::FromName(name));
	}

	uint8 WidgetIndex = static_cast<uint8>(type) - 1;
	if (WS_01->GetActiveWidgetIndex() < WidgetIndex)
		WS_01->SetActiveWidgetIndex(0);
	else
	{
		WS_01->SetActiveWidgetIndex(WidgetIndex);
	}

	if (this->GetVisibility() == ESlateVisibility::Hidden)
		this->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UInteractionHUD::DeactiveWidget()
{
	this->SetVisibility(ESlateVisibility::Hidden);
}

void UInteractionHUD::ChangeName(FName name)
{
	TB_Name->SetText(FText::FromName(name));
}
