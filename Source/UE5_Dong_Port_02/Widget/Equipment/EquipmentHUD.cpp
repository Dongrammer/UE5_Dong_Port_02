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

	// 
	Slots.Add(EEquipType::E_Head, Slot_Head);
	Slots.Add(EEquipType::E_Chest, Slot_Chest);
	Slots.Add(EEquipType::E_Legs, Slot_Legs);
	Slots.Add(EEquipType::E_Feet, Slot_Feet);
	Slots.Add(EEquipType::E_Hands, Slot_Hands);
	Slots.Add(EEquipType::E_Weapon, Slot_Weapon);
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
	temp = MouseXY - this->GetRenderTransform().Translation;
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
	this->SetRenderTransform(transform);
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

void UEquipmentHUD::SetSlotImage(EEquipType type, UTexture2D* image, const FLinearColor* color)
{
	switch (type)
	{
	case EEquipType::E_Head:
	{
		Slot_Head->SetSlotImage(image, color);
		break;
	}
	case EEquipType::E_Chest:
	{
		Slot_Chest->SetSlotImage(image, color);
		break;
	}
	case EEquipType::E_Legs:
	{
		Slot_Legs->SetSlotImage(image, color);
		break;
	}
	case EEquipType::E_Feet:
	{
		Slot_Feet->SetSlotImage(image, color);
		break;
	}
	case EEquipType::E_Hands:
	{
		Slot_Hands->SetSlotImage(image, color);
		break;
	}
	case EEquipType::E_Weapon:
	{
		Slot_Weapon->SetSlotImage(image, color);
		break;
	}
	}
}

void UEquipmentHUD::InitSlotImage(EEquipType type)
{
	switch (type)
	{
	case EEquipType::E_Head:
	{
		Slot_Head->InitSlotImage();
		break;
	}
	case EEquipType::E_Chest:
	{
		Slot_Chest->InitSlotImage();
		break;
	}
	case EEquipType::E_Legs:
	{
		Slot_Legs->InitSlotImage();
		break;
	}
	case EEquipType::E_Feet:
	{
		Slot_Feet->InitSlotImage();
		break;
	}
	case EEquipType::E_Hands:
	{
		Slot_Hands->InitSlotImage();
		break;
	}
	case EEquipType::E_Weapon:
	{
		Slot_Weapon->InitSlotImage();
		break;
	}
	default:
	{
		return;
	}
	}
}
