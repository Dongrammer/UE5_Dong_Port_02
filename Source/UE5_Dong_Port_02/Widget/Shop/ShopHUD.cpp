#include "Widget/Shop/ShopHUD.h"
#include "Components/CanvasPanel.h"
#include "Components/SizeBox.h"
#include "Components/Button.h"
#include "Components/ListView.h"
#include "ShopItemListObject.h"
#include "TPS_GameInstance.h"
#include "Component/ItemComponent.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Character/Hero.h"

void UShopHUD::NativeConstruct()
{
	Super::NativeConstruct();

	UTPS_GameInstance* GameInstance = Cast<UTPS_GameInstance>(GetWorld()->GetGameInstance());
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("ShopHUD : GameInstance Is NULL !!"));
		return;
	}

	ItemComponent = GameInstance->GetItemComponent();
	if (!ItemComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("ShopHUD : ItemComponent Is NULL !!"));
		return;
	}

	FScriptDelegate ExitPressed;
	ExitPressed.BindUFunction(this, "ExitPressed");
	Bt_Exit->OnClicked.Add(ExitPressed);

	FScriptDelegate TradePressed;
	TradePressed.BindUFunction(this, "TradePressed");
	Bt_Trade->OnClicked.Add(TradePressed);
}

void UShopHUD::ActiveHUD(TArray<FItem> PlayerItems, TArray<FItemData> SellingItems, float AdjValue, EItemType shopitemtype)
{
	ValueAdjust = AdjValue;
	ShopItemType = shopitemtype;

	TB_PlayerGold->SetText(FText::FromString(FString::Printf(TEXT(" %d "), OwnerPlayer->GetCurrentGold())));

	for (FItem item : PlayerItems)
	{
		FItemDataTableBase data = ItemComponent->GetDataTableBase(item.ItemData);
		TObjectPtr<UShopItemListObject> object = NewObject<UShopItemListObject>(this, UShopItemListObject::StaticClass());
		object->ItemData = item.ItemData;
		object->ItemDataTable = data;
		object->ItemCount = item.count;
		object->Value = data.SellingValue;
		object->DClickSlot.BindUFunction(this, "PlayerItemListClick");

		LV_PlayerItemList->AddItem(object);
	}

	for (FItemData item : SellingItems)
	{
		FItemDataTableBase data = ItemComponent->GetDataTableBase(item);
		TObjectPtr<UShopItemListObject> object = NewObject<UShopItemListObject>(this, UShopItemListObject::StaticClass());
		object->ItemData = item;
		object->ItemDataTable = data;
		object->ItemCount = 1;
		object->Value = data.PurchaseValue * ValueAdjust;
		object->DClickSlot.BindUFunction(this, "ShopItemListClick");

		LV_ShopItemList->AddItem(object);
	}
}

void UShopHUD::ExitPressed()
{
	if (DShopHUDToggle.IsBound())
		DShopHUDToggle.Execute();

	/* ========== Init HUD ========== */ 
	// 
	{
		TArray<UObject*> RemoveObject;

		for (UObject* ToSellObj : LV_ToSellItemList->GetListItems())
		{
			TObjectPtr<UShopItemListObject> obj = Cast<UShopItemListObject>(ToSellObj);
			if (obj)
			{
				RemoveObject.Add(obj);
			}
		}
		for (UObject* obj : RemoveObject)
		{
			LV_ToSellItemList->RemoveItem(obj);
			obj->MarkAsGarbage();
		}
	}
	// 
	{
		TArray<UObject*> RemoveObject;

		for (UObject* ToBuyObj : LV_ToBuyItemList->GetListItems())
		{
			TObjectPtr<UShopItemListObject> obj = Cast<UShopItemListObject>(ToBuyObj);
			if (obj)
			{
				RemoveObject.Add(obj);
			}
		}

		for (UObject* obj : RemoveObject)
		{
			LV_ToBuyItemList->RemoveItem(obj);
			obj->MarkAsGarbage();
		}
	}
	// 
	{
		TArray<UObject*> RemoveObject;

		for (UObject* PlayerObj : LV_PlayerItemList->GetListItems())
		{
			TObjectPtr<UShopItemListObject> obj = Cast<UShopItemListObject>(PlayerObj);
			if (obj)
			{
				RemoveObject.Add(obj);
			}
		}

		for (UObject* obj : RemoveObject)
		{
			LV_PlayerItemList->RemoveItem(obj);
			obj->MarkAsGarbage();
		}
	}
	// 
	{
		TArray<UObject*> RemoveObject;

		for (UObject* ShopObj : LV_ShopItemList->GetListItems())
		{
			TObjectPtr<UShopItemListObject> obj = Cast<UShopItemListObject>(ShopObj);
			if (obj)
			{
				RemoveObject.Add(obj);
			}
		}

		for (UObject* obj : RemoveObject)
		{
			LV_ShopItemList->RemoveItem(obj);
			obj->MarkAsGarbage();
		}
	}
	
	// Init Gold
	MinTradeGold = 0;
	MaxTradeGold = 0;
	TB_MinTradeGold->SetText(FText::FromString(FString::Printf(TEXT("0"))));
	TB_MaxTradeGold->SetText(FText::FromString(FString::Printf(TEXT("0"))));
}

void UShopHUD::TradePressed()
{
	if ((OwnerPlayer->GetCurrentGold() + MinTradeGold) < 0)
	{
		PlayAnimation(AN_NoMoney);
		return;
	}

	int CalculatedGold = 0;
	// Player Item Remove
	{
		TArray<UObject*> RemoveObject;
		for (UObject* ToSellObj : LV_ToSellItemList->GetListItems())
		{
			TObjectPtr<UShopItemListObject> obj = Cast<UShopItemListObject>(ToSellObj);
			if (obj)
			{
				for (int i = 0; i < obj->ItemCount; i++)
				{
					OwnerPlayer->ItemUse(obj->ItemData);

					// Check Item Type
					if (obj->ItemData.ItemType != ShopItemType)
					{
						CalculatedGold += SetRandomValue(obj->Value);
					}
					else
					{
						CalculatedGold += obj->Value;
					}
				}

				RemoveObject.Add(obj);
			}
		}

		for (UObject* obj : RemoveObject)
		{
			LV_ToSellItemList->RemoveItem(obj);
			obj->MarkAsGarbage();
		}
	}

	// Player Get Item
	{
		TArray<UObject*> RemoveObject;
		for (UObject* ToBuyObj : LV_ToBuyItemList->GetListItems())
		{
			TObjectPtr<UShopItemListObject> obj = Cast<UShopItemListObject>(ToBuyObj);
			if (obj)
			{
				OwnerPlayer->GetItems(obj->ItemData, obj->ItemCount);
				CalculatedGold -= (obj->Value * obj->ItemCount);

				RemoveObject.Add(obj);
			}
		}

		for (UObject* obj : RemoveObject)
		{
			LV_ToBuyItemList->RemoveItem(obj);
			obj->MarkAsGarbage();
		}
	}

	// Player Gold Update
	OwnerPlayer->GetGold(CalculatedGold);
	TB_PlayerGold->SetText(FText::FromString(FString::Printf(TEXT(" %d "), OwnerPlayer->GetCurrentGold())));

	// Init Gold
	MinTradeGold = 0;
	MaxTradeGold = 0;
	TB_MinTradeGold->SetText(FText::FromString(FString::Printf(TEXT("0"))));
	TB_MaxTradeGold->SetText(FText::FromString(FString::Printf(TEXT("0"))));

	// Refresh Player Item List
	{
		TArray<UObject*> RemoveObject;

		for (UObject* PlayerObj : LV_PlayerItemList->GetListItems())
		{
			TObjectPtr<UShopItemListObject> obj = Cast<UShopItemListObject>(PlayerObj);
			if (obj)
			{
				RemoveObject.Add(obj);
			}
		}

		for (UObject* obj : RemoveObject)
		{
			LV_PlayerItemList->RemoveItem(obj);
			obj->MarkAsGarbage();
		}
	}

	TArray<FItem> playerItems = OwnerPlayer->GetHaveItems();
	for (FItem item : playerItems)
	{
		FItemDataTableBase data = ItemComponent->GetDataTableBase(item.ItemData);
		TObjectPtr<UShopItemListObject> object = NewObject<UShopItemListObject>(this, UShopItemListObject::StaticClass());
		object->ItemData = item.ItemData;
		object->ItemDataTable = data;
		object->ItemCount = item.count;
		object->Value = data.SellingValue;
		object->DClickSlot.BindUFunction(this, "PlayerItemListClick");

		LV_PlayerItemList->AddItem(object);
	}
}

void UShopHUD::PlayerItemListClick(UShopItemListObject* object)
{
	object->CountUp(-1);

	bool c = false;
	// if ToSellList already have item
	for (UObject* ToSellobj : LV_ToSellItemList->GetListItems())
	{
		TObjectPtr<UShopItemListObject> obj = Cast<UShopItemListObject>(ToSellobj);

		if (obj)
		{
			if ((obj->ItemData.ItemType == object->ItemData.ItemType) && (obj->ItemData.ItemID == object->ItemData.ItemID))
			{
				obj->CountUp(1);
				obj->ValueMultCount();
				c = true;

				// Check Item Type
				if (obj->ItemData.ItemType != ShopItemType)
				{
					SetTradeGoldNotType(obj->Value);
				}
				else
				{
					SetTradeGold(obj->Value);
				}

				break;
			}
		}
	}
	// ToSellList don't have item
	if (!c)
	{
		FItemDataTableBase data = ItemComponent->GetDataTableBase(object->ItemData);
		TObjectPtr<UShopItemListObject> NewObj = NewObject<UShopItemListObject>(this, UShopItemListObject::StaticClass());

		NewObj->ItemData = object->ItemData;
		NewObj->ItemDataTable = data;
		NewObj->ItemCount = 1;
		NewObj->Value = data.SellingValue;
		NewObj->DClickSlot.BindUFunction(this, "ToSellItemListClick");

		LV_ToSellItemList->AddItem(NewObj);

		// Check Item Type
		if (NewObj->ItemData.ItemType != ShopItemType)
		{
			SetTradeGoldNotType(NewObj->Value);
		}
		else
		{
			SetTradeGold(NewObj->Value);
		}
	}

	// Check object Count
	if (object->ItemCount <= 0)
	{
		LV_PlayerItemList->RemoveItem(object);
		object->MarkAsGarbage();
	}
}

void UShopHUD::ToSellItemListClick(UShopItemListObject* object)
{
	object->CountUp(-1);
	object->ValueMultCount();

	bool c = false;
	// if PlayerList already have item
	for (UObject* Playerobj : LV_PlayerItemList->GetListItems())
	{
		TObjectPtr<UShopItemListObject> obj = Cast<UShopItemListObject>(Playerobj);

		if (obj)
		{
			if ((obj->ItemData.ItemType == object->ItemData.ItemType) && (obj->ItemData.ItemID == object->ItemData.ItemID))
			{
				obj->CountUp(1);
				c = true;

				// Check Item Type
				if (obj->ItemData.ItemType != ShopItemType)
				{
					SetTradeGoldNotType(-obj->Value);
				}
				else
				{
					SetTradeGold(-obj->Value);
				}

				break;
			}
		}
	}
	// PlayerList don't have item
	if (!c)
	{
		FItemDataTableBase data = ItemComponent->GetDataTableBase(object->ItemData);
		TObjectPtr<UShopItemListObject> NewObj = NewObject<UShopItemListObject>(this, UShopItemListObject::StaticClass());

		NewObj->ItemData = object->ItemData;
		NewObj->ItemDataTable = data;
		NewObj->ItemCount = 1;
		NewObj->Value = data.SellingValue;
		NewObj->DClickSlot.BindUFunction(this, "PlayerItemListClick");

		LV_PlayerItemList->AddItem(NewObj);

		// Check Item Type
		if (NewObj->ItemData.ItemType != ShopItemType)
		{
			SetTradeGoldNotType(-NewObj->Value);
		}
		else
		{
			SetTradeGold(-NewObj->Value);
		}

	}

	// Check object Count
	if (object->ItemCount <= 0)
	{
		LV_ToSellItemList->RemoveItem(object);
		object->MarkAsGarbage();
	}
}

void UShopHUD::ToBuyItemListClick(UShopItemListObject* object)
{
	object->CountUp(-1);
	object->ValueMultCount();
	SetTradeGold(object->Value);

	if (object->ItemCount <= 0)
	{
		LV_ToBuyItemList->RemoveItem(object);
		object->MarkAsGarbage();
	}
}

void UShopHUD::ShopItemListClick(UShopItemListObject* object)
{
	bool c = false;
	// if ToBuyList already have item
	for (UObject* ToBuyobj : LV_ToBuyItemList->GetListItems())
	{
		TObjectPtr<UShopItemListObject> obj = Cast<UShopItemListObject>(ToBuyobj);

		if (obj)
		{
			if ((obj->ItemData.ItemType == object->ItemData.ItemType) && (obj->ItemData.ItemID == object->ItemData.ItemID))
			{
				obj->CountUp(1);
				obj->ValueMultCount();
				c = true;
				SetTradeGold(-obj->Value);
				break;
			}
		}
	}

	if (!c)
	{
		FItemDataTableBase data = ItemComponent->GetDataTableBase(object->ItemData);
		TObjectPtr<UShopItemListObject> NewObj = NewObject<UShopItemListObject>(this, UShopItemListObject::StaticClass());

		NewObj->ItemData = object->ItemData;
		NewObj->ItemDataTable = data;
		NewObj->ItemCount = 1;
		NewObj->Value = data.PurchaseValue * ValueAdjust;
		NewObj->DClickSlot.BindUFunction(this, "ToBuyItemListClick");

		LV_ToBuyItemList->AddItem(NewObj);
		SetTradeGold(-NewObj->Value);
	}
}

void UShopHUD::SetTradeGold(int value)
{
	MinTradeGold += value;
	MaxTradeGold += value;

	FString str1 = FString::Printf(TEXT("%d"), MinTradeGold);
	if (MinTradeGold >= 0)
	{
		FString s1 = TEXT("+");
		str1 = s1.Append(str1);
	}
	TB_MinTradeGold->SetText(FText::FromString(str1));

	FString str2 = FString::Printf(TEXT("%d"), MaxTradeGold);
	if (MaxTradeGold >= 0)
	{
		FString s2 = TEXT("+");
		str2 = s2.Append(str2);
	}
	TB_MaxTradeGold->SetText(FText::FromString(str2));
	/*int PurchasePrice = 0;
	if (LV_ToBuyItemList->GetNumItems() >= 0)
	{
		for (UObject* ToBuyobj : LV_ToBuyItemList->GetListItems())
		{

		}

	}

	int SellingPrice = 0;
	if (LV_ToSellItemList->GetNumItems() >= 0)
	{
	}*/
}

void UShopHUD::SetTradeGoldNotType(int value)
{
	MinTradeGold += value * ToSellRandomValueMin;
	MaxTradeGold += value * ToSellRandomValueMax;

	FString str1 = FString::Printf(TEXT("%d"), MinTradeGold);
	if (MinTradeGold >= 0)
	{
		FString s1 = TEXT("+");
		str1 = s1.Append(str1);
	}
	TB_MinTradeGold->SetText(FText::FromString(str1));

	FString str2 = FString::Printf(TEXT("%d"), MaxTradeGold);
	if (MaxTradeGold >= 0)
	{
		FString s2 = TEXT("+");
		str2 = s2.Append(str2);
	}
	TB_MaxTradeGold->SetText(FText::FromString(str2));
}

int UShopHUD::SetRandomValue(int val)
{
	float rand = FMath::RandRange(ToSellRandomValueMin, ToSellRandomValueMax);
	
	return val * rand;
}
