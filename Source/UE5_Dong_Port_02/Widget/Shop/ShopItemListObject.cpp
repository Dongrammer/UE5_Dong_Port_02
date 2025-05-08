#include "Widget/Shop/ShopItemListObject.h"

void UShopItemListObject::CountUp(int count)
{
	ItemCount += count;
	if (DItemCountUp.IsBound()) DItemCountUp.Execute();
}

void UShopItemListObject::ValueMultCount()
{
	CountMultValue = Value * ItemCount;
	if (DCountMultValue.IsBound()) DCountMultValue.Execute();
}