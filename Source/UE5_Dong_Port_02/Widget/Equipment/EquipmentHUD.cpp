#include "Widget/Equipment/EquipmentHUD.h"

#include "Components/SizeBox.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Widget/Equipment/EquipSlot.h"

void UEquipmentHUD::NativeConstruct()
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

void UEquipmentHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
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

void UEquipmentHUD::HeadPressed()
{
	ShouldMove = true;

	//temp = FVector2D(0, 0);
	FVector2D MouseXY = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	temp = MouseXY - SB_Body->GetRenderTransform().Translation;
}

void UEquipmentHUD::HeadReleased()
{
	ShouldMove = false;
}

void UEquipmentHUD::ExitPressed()
{
	if (DToggle.IsBound()) DToggle.Execute();
}

void UEquipmentHUD::MovePosition()
{
	FVector2D MouseXY = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());

	FWidgetTransform transform;
	transform.Translation = MouseXY - temp;
	SB_Body->SetRenderTransform(transform);
}

void UEquipmentHUD::ToggleHUD()
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
