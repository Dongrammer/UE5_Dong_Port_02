#include "Widget/Technique/TechniqueNodeInfoHUD.h"

#include "Components/SizeBox.h"
#include "Components/Border.h"
#include "Components/HorizontalBox.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "Components/RichTextBlock.h"

void UTechniqueNodeInfoHUD::InfoSetting(FNodeInfoData data)
{
	TB_NodeName->SetText(data.NodeName);
	TB_NodeDescription->SetText(data.NodeDescription);
	TB_NodeTP->SetText(FText::AsNumber(data.RequireTP));
}
