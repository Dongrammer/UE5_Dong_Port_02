#include "Widget/Status/StatusHUD.h"

#include "Components/SizeBox.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Components/VerticalBox.h"
#include "Components/Image.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/TextBlock.h"

void UStatusHUD::NativeConstruct()
{
	Super::NativeConstruct();

	// Button Bind Function
	FScriptDelegate Pressed, Released;
	Pressed.BindUFunction(this, "HeadPressed");
	Released.BindUFunction(this, "HeadReleased");
	BT_Head->OnPressed.Add(Pressed);
	BT_Head->OnReleased.Add(Released);

	FScriptDelegate ExitPressed;
	ExitPressed.BindUFunction(this, "ExitPressed");
	BT_Exit->OnPressed.Add(ExitPressed);

}

void UStatusHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (ShouldMove)
	{
		float MouseX, MouseY;
		MouseX = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld()).X;
		MouseY = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld()).Y;
		MovePosition();
	}
}

void UStatusHUD::HeadPressed()
{
	ShouldMove = true;

	//temp = FVector2D(0, 0);
	FVector2D MouseXY = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	temp = MouseXY - this->GetRenderTransform().Translation;
}

void UStatusHUD::HeadReleased()
{
	ShouldMove = false;
}

void UStatusHUD::ExitPressed()
{
	if (DToggle.IsBound()) DToggle.Execute();
}

void UStatusHUD::MovePosition()
{
	FVector2D MouseXY = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());

	FWidgetTransform transform;
	transform.Translation = MouseXY - temp;
	this->SetRenderTransform(transform);
}

void UStatusHUD::ToggleHUD()
{
	if (this->GetVisibility() == ESlateVisibility::Hidden)
	{
		this->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		this->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UStatusHUD::UpdateLevel(uint8 level)
{
	FText t = FText::AsNumber(level);
	TB_C_Level->SetText(t);
	
}

void UStatusHUD::UpdateHP(int mhp, int hp)
{
	FText t = FText::FromString(FString::Printf(TEXT("%d / %d"), hp, mhp));
	TB_C_HP->SetText(t);
}
