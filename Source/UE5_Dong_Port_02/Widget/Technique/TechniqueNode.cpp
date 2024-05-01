#include "Widget/Technique/TechniqueNode.h"

#include "Components/SizeBox.h"
#include "Components/Overlay.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "Action/BaseAction.h"

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
}

void UTechniqueNode::Bt_Main_Clicked()
{
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

void UTechniqueNode::AddActionLevel()
{
	ActionLevel++;
	ActionLevelSetting();
}

void UTechniqueNode::ActionLevelSetting()
{
	Tx_Level->SetText(FText::FromString(FString::Printf(TEXT("( %d / %d )"), ActionLevel, MaxActionLevel)));
}
