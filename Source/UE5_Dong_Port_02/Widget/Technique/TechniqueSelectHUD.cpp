#include "Widget/Technique/TechniqueSelectHUD.h"

#include "Components/CanvasPanel.h"
#include "Components/SizeBox.h"
#include "Components/Overlay.h"
#include "Components/Image.h"
#include "Components/HorizontalBox.h"
#include "Components/ListView.h"

#include "Widget/Technique/TechniqueSelectNodeSpace.h"


void UTechniqueSelectHUD::NativeConstruct()
{
	Super::NativeConstruct();

	NodeSpace_01->SpaceNum = 0;
	NodeSpaces.Add(NodeSpace_01);
	NodeSpace_02->SpaceNum = 1;
	NodeSpaces.Add(NodeSpace_02);
	NodeSpace_03->SpaceNum = 2;
	NodeSpaces.Add(NodeSpace_03);
	NodeSpace_04->SpaceNum = 3;
	NodeSpaces.Add(NodeSpace_04);
	NodeSpace_05->SpaceNum = 4;
	NodeSpaces.Add(NodeSpace_05);
}

void UTechniqueSelectHUD::AddNode(UTechniqueNode* node)
{
	for (TObjectPtr<UTechniqueSelectNodeSpace> NodeSpace : NodeSpaces)
	{
		NodeSpace->AddNode(node);
	}
}
