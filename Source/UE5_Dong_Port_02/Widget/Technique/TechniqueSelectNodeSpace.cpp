#include "Widget/Technique/TechniqueSelectNodeSpace.h"

#include "Components/SizeBox.h"
#include "Components/Overlay.h"
#include "Components/ListView.h"
#include "Components/Button.h"
#include "Components/Image.h"

#include "Widget/Technique/TechniqueSelectNodeObject.h"
#include "Technique/TechniqueNodeActive.h"
#include "Action/BaseAction.h"

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

void UTechniqueSelectNodeSpace::AddNode(UTechniqueNodeActive* node)
{
	if (!node)
	{
		UE_LOG(LogTemp, Warning, TEXT("TechniqueNodeSpace : Node Is NULL !!"));
		return;
	}

	if (node->GetAction().WeaponType == EWeaponType::E_None)
	{
		UE_LOG(LogTemp, Warning, TEXT("TechniqueNodeSpace : Added Node Action Is NULL !!"));
		return;
	}
	/*
	// Set FName
	FName NodeFName;
	switch (node->GetAction()->GetWeaponType())
	{
	case EWeaponType::E_Gauntlet:
	{
		NodeFName = FName(*FString::Printf(TEXT("Gauntlet Action - %d"), node->GetAction()->));
		break;
	}
	case EWeaponType::E_OneHandSword:
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
	*/
	TObjectPtr<UTechniqueSelectNodeObject> NodeObject = NewObject<UTechniqueSelectNodeObject>(this, UTechniqueSelectNodeObject::StaticClass());
	
	NodeObject->action = node->GetAction();
	NodeObject->Icon = node->Icon;
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
