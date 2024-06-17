#include "Widget/Technique/TechniqueNodeHUD.h"

#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/SizeBox.h"
#include "Components/Overlay.h"

#include "Action/ActionData.h"
#include "Widget/Technique/TechniqueNode.h"
#include "Action/ActionDataAsset.h"
#include "Helper.h"

void UTechniqueNodeHUD::NativeConstruct()
{
	Super::NativeConstruct();
}

void UTechniqueNodeHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

FReply UTechniqueNodeHUD::NativeOnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FVector2D Scale = CP_01->GetRenderTransform().Scale;
	FVector2D Value = { 0.05, 0.05 };	// Reduction Value

	float WheelDelta = InMouseEvent.GetWheelDelta();

	if (WheelDelta > 0 && Scale.ComponentwiseAllLessThan(FVector2D(2, 2)))
	{
		CP_01->SetRenderScale(Scale + Value);
		return FReply::Handled();
	}
	else if (WheelDelta < 0 && Scale.ComponentwiseAllGreaterThan(FVector2D(0.5, 0.5)))
	{
		CP_01->SetRenderScale(Scale - Value);
		return FReply::Handled();
	}

	return FReply::Unhandled();
}

FReply UTechniqueNodeHUD::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	MouseButtonDown = true;

	FVector2D MouseXY = InMouseEvent.GetScreenSpacePosition();
	temp = MouseXY - CP_01->GetRenderTransform().Translation;

	return FReply::Handled();
}

FReply UTechniqueNodeHUD::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	MouseButtonDown = false;

	return FReply::Handled();
}

FReply UTechniqueNodeHUD::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (!MouseButtonDown)
	{
		return FReply::Unhandled();
	}
	
	FVector2D MouseXY = InMouseEvent.GetScreenSpacePosition();

	FWidgetTransform transform;
	transform.Translation = MouseXY - temp;
	transform.Scale = CP_01->GetRenderTransform().Scale;

	CP_01->SetRenderTransform(transform);

	return FReply::Handled();
}

void UTechniqueNodeHUD::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	MouseButtonDown = false;
}
