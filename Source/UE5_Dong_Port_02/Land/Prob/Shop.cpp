#include "Land/Prob/Shop.h"
#include "Item/BaseItem.h"

AShop::AShop()
{
	ProbType = EProbType::E_WorkingProb;
	WorkType = EWorkType::E_ShopKeeper;
	bCanPlayerUse = false;
}

void AShop::Active(ABaseHuman* human)
{
	Super::Active(human);

	human->SetActorRotation(ActiveMeshIn->GetComponentRotation() + FRotator(0, 90, 0));
}

void AShop::Deactive(ABaseHuman* human)
{
	Super::Deactive(human);
}
//
//TArray<FItemData> AShop::GetSellingItemData()
//{
//	TArray<FItemData> itemsdata;
//
//	for (TSubclassOf<ABaseItem> item : SellingItems)
//	{
//		item->
//		itemsdata.Add()
//	}
//
//	return TArray<FItemData>();
//}
