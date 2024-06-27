#include "Widget/Inventory/InventoryHUD.h"
#include "Components/ListView.h"
#include "Item/ItemData.h"
#include "InventorySlot.h"
#include "InventorySlotObject.h"
#include "Helper.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/SizeBox.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Component/InventoryComponent.h"

void UInventoryHUD::NativeConstruct()
{
	Super::NativeConstruct();

	// Button Bind Function
	FScriptDelegate Pressed, Released;
	Pressed.BindUFunction(this, "HeadPressed");
	Released.BindUFunction(this, "HeadReleased");
	Button_Head->OnPressed.Add(Pressed);
	Button_Head->OnReleased.Add(Released);

	FScriptDelegate ExitPressed;
	ExitPressed.BindUFunction(this, "ExitPressed");
	Button_Exit->OnPressed.Add(ExitPressed);
}

void UInventoryHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
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

void UInventoryHUD::HeadPressed()
{
	ShouldMove = true;

	//temp = FVector2D(0, 0);
	FVector2D MouseXY = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	temp = MouseXY - this->GetRenderTransform().Translation;
}

void UInventoryHUD::HeadReleased()
{
	ShouldMove = false;
}

void UInventoryHUD::ExitPressed()
{
	if (DToggle.IsBound()) DToggle.Execute();
}

void UInventoryHUD::MovePosition()
{
	FVector2D MouseXY = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());

	FWidgetTransform transform;
	transform.Translation = MouseXY - temp;
	this->SetRenderTransform(transform);
}

void UInventoryHUD::ToggleHUD()
{
	if (this->GetVisibility() == ESlateVisibility::Hidden)
	{
		this->SetVisibility(ESlateVisibility::Visible);

		/*FInputModeGameAndUI InputMode;
		InputMode.SetWidgetToFocus(this->TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		InputMode.SetHideCursorDuringCapture(false);
		HeroController->SetInputMode(InputMode);*/
	}
	else
	{
		this->SetVisibility(ESlateVisibility::Hidden);

		//FInputModeGameOnly InputMode;
		//HeroController->SetInputMode(InputMode);
	}
}

void UInventoryHUD::AddItem(const FItemData data, const FItemDataTableBase additem, const int count)
{
	// Create Data Object
	int32 C = ItemList->GetNumItems();
	FString SlotNameFString = FString::Printf(TEXT("Slot_%d"), C);
	FName SlotNameFName(*SlotNameFString);
	TObjectPtr<UInventorySlotObject> ItemObject = NewObject<UInventorySlotObject>(this, UInventorySlotObject::StaticClass(), SlotNameFName);
	
	ItemObject->ItemDataTable.Name = additem.Name;
	ItemObject->ItemDataTable.Rarity = additem.Rarity;
	ItemObject->ItemDataTable.Texture = additem.Texture;
	ItemObject->ItemDataTable.Weight = additem.Weight;
	ItemObject->ItemCount = count;
	ItemObject->ItemData = data;
	ItemObject->DItemUse.AddUFunction(this, "ItemUse");
	ItemObject->DItemClick.AddUFunction(this, "ItemClick");

	ItemList->AddItem(ItemObject);
}

void UInventoryHUD::CountUpItem(const int index, const int count)
{
	UInventorySlotObject* IndexObject = Cast<UInventorySlotObject>(ItemList->GetItemAt(index));
	if (IndexObject)
	{
		IndexObject->CountUp(count);
	}
}

void UInventoryHUD::RemoveItem(const int index)
{
	ItemList->RemoveItem(ItemList->GetItemAt(index));
}

void UInventoryHUD::SetTextWeight(float max, float current)
{
	Text_Weight->SetText(FText::FromString(FString::Printf(TEXT("( %0.2f / %0.2f )"), current, max)));
}

//void UInventoryHUD::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
//{
//	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
//
//	InventoryComponent->SetFocusHUD();
//}
//
//void UInventoryHUD::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
//{
//	Super::NativeOnMouseLeave(InMouseEvent);
//
//	InventoryComponent->SetFocusInit();
//}

void UInventoryHUD::ItemUse(FItemData item)
{
	InventoryComponent->ItemUse(item);
}

void UInventoryHUD::ItemClick(FItemData item)
{
	InventoryComponent->ItemClick(item);
}
