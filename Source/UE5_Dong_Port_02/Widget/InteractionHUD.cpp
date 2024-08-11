#include "Widget/InteractionHUD.h"

#include "Components/CanvasPanel.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"

void UInteractionHUD::SetName(FName name)
{
	if (name == "")
	{
		TB_Name->SetText(FText::FromString("???"));
		return;
	}

	TB_Name->SetText(FText::FromName(name));
}

void UInteractionHUD::SetPosition(FVector2D position)
{
	SB_Body->SetRenderTranslation(position);
}
