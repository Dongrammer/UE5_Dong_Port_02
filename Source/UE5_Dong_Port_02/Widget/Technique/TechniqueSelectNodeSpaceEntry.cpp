#include "Widget/Technique/TechniqueSelectNodeSpaceEntry.h"

#include "Components/SizeBox.h"
#include "Components/Image.h"
#include "Components/Button.h"

#include "Widget/Technique/TechniqueSelectNodeObject.h"

void UTechniqueSelectNodeSpaceEntry::NativeConstruct()
{
	Super::NativeConstruct();

	FScriptDelegate Clicked;
	Clicked.BindUFunction(this, "MainButtonClicked");
	BT_Main->OnClicked.Add(Clicked);
}

void UTechniqueSelectNodeSpaceEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	node = Cast<UTechniqueSelectNodeObject>(ListItemObject);

	if (!node)
	{
		UE_LOG(LogTemp, Warning, TEXT("TechniqueSelectNodeSpaceEntry : NodeObject is NULL !!"));
		return;
	}

	if (node->image)
	{
		FSlateBrush brush = node->image->GetBrush();
		IM_Base->SetBrush(brush);
	}

	action = node->action;

}

void UTechniqueSelectNodeSpaceEntry::MainButtonClicked()
{
	if (node->DSelectNode.IsBound()) node->DSelectNode.Broadcast(action, IM_Base);
}
