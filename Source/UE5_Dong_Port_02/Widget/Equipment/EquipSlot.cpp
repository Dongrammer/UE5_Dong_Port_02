#include "Widget/Equipment/EquipSlot.h"

#include "Components/SizeBox.h"
#include "Components/Border.h"
#include "Components/Image.h"

void UEquipSlot::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (EmptyImage)
	{
		IM_Base->SetBrushFromTexture(EmptyImage);
		IM_Base->SetOpacity(0.5f);
	}
}

void UEquipSlot::SetSlotImage(UTexture2D* image, const FLinearColor* color)
{
	if (!color)
	{
		UE_LOG(LogTemp, Warning, TEXT("EquipSlot : color Is NULL !!"));
		return;
	}

	IM_Base->SetVisibility(ESlateVisibility::Hidden);
	IM_Item->SetBrushFromTexture(image);
	IM_Item->SetVisibility(ESlateVisibility::Visible);
	FColor c = color->ToFColor(true);	
	IM_Rarity->GetDynamicMaterial()->SetVectorParameterValue("Color", c);
	IM_Rarity->SetVisibility(ESlateVisibility::Visible);
}
