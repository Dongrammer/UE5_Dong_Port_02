#include "Widget/Technique/TechniqueNodeHUD.h"

#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
void UTechniqueNodeHUD::NativeConstruct()
{
	Super::NativeConstruct();

	//FScriptDelegate BackgroundHovered, BackgroundUnHovered;
	//BackgroundHovered.BindUFunction(this, "BackgroundHovered");
	//BackgroundUnHovered.BindUFunction(this, "BackgroundUnHovered");
	//Button_Background->OnHovered.Add(BackgroundHovered);
	//Button_Background->OnHovered.Add(BackgroundUnHovered);
}

void UTechniqueNodeHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	//if (bBackgroundHovered)
	//{
//
	//}
}

FReply UTechniqueNodeHUD::NativeOnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FVector2D Scale = Canvas->RenderTransform.Scale;
	FVector2D Value = { 0.02, 0.02 };	// Reduction Value

	float WheelDelta = InMouseEvent.GetWheelDelta();

	if (WheelDelta > 0 && Scale < FVector2D(1, 1))
	{
		Canvas->SetRenderScale(Scale + Value);
		return FReply::Handled();
	}
	else if (WheelDelta < 0 && Scale > FVector2D(0.1, 0.1))
	{
		Canvas->SetRenderScale(Scale - Value);
		return FReply::Handled();
	}

	return FReply::Unhandled();
}

//void UTechniqueNodeHUD::BackgroundHovered()
//{
//	bBackgroundHovered = true;
//}

//void UTechniqueNodeHUD::BackgroundUnHovered()
//{
//	bBackgroundHovered = false;
//}
