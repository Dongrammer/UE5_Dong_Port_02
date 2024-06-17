#include "Widget/Technique/TechniqueSelectNodeSpace.h"

#include "Components/SizeBox.h"
#include "Components/Overlay.h"
#include "Components/ListView.h"
#include "Components/Button.h"
#include "Components/Image.h"

#include "Widget/Technique/TechniqueSelectNodeObject.h"
#include "Widget/Technique/TechniqueNode.h"

void UTechniqueSelectNodeSpace::NativeConstruct()
{
	ActionList->SetVisibility(ESlateVisibility::Hidden);

	FScriptDelegate Clicked;
	Clicked.BindUFunction(this, "MainButtonClicked");
	Bt_Main->OnClicked.Add(Clicked);;
}

void UTechniqueSelectNodeSpace::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	ActionList->SetVisibility(ESlateVisibility::Hidden);
}

void UTechniqueSelectNodeSpace::AddNode(UTechniqueNode* node)
{
	if (!node)
	{
		UE_LOG(LogTemp, Warning, TEXT("TechniqueNodeSpace : Node Is NULL !!"));
		return;
	}

	if (node->GetAction().ActionType == EActionType::E_None)
	{
		UE_LOG(LogTemp, Warning, TEXT("TechniqueNodeSpace : Added Node Action Is NULL !!"));
		return;
	}

	// Set FName
	FName NodeFName;
	switch (node->GetAction().ActionType)
	{
	case EActionType::E_Gauntlet:
	{
		NodeFName = FName(*FString::Printf(TEXT("Gauntlet Action - %d"), node->GetAction().ActionNumber));
		break;
	}
	case EActionType::E_Sword:
	{
		NodeFName = FName(*FString::Printf(TEXT("Sword Action - %d"), node->GetAction().ActionNumber));
		break;
	}
	default:
	{
		NodeFName = "NULL";
		break;
	}
	}

	TObjectPtr<UTechniqueSelectNodeObject> NodeObject = NewObject<UTechniqueSelectNodeObject>(this, UTechniqueSelectNodeObject::StaticClass(), NodeFName);
	
	NodeObject->action = node->GetAction();
	NodeObject->image = node->GetImage();
	NodeObject->DSelectNode.AddUFunction(this, "SelectNodeDelegate");

	ActionList->AddItem(NodeObject);
}

void UTechniqueSelectNodeSpace::MainButtonClicked()
{
	ActionList->SetVisibility(ESlateVisibility::Visible);
}

void UTechniqueSelectNodeSpace::SelectNodeDelegate(FActionData action, UImage* image)
{
	FSlateBrush brush = image->GetBrush();
	IM_Main->SetBrush(brush);
	if (DSelectAction.IsBound()) DSelectAction.Broadcast(action, SpaceNum);
}
