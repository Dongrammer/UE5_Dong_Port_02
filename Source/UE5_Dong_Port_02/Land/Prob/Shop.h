#pragma once

#include "CoreMinimal.h"
#include "Land/Prob/BaseProb.h"
#include "Shop.generated.h"

class ABaseItem;

/*
	Shop must be included in the building's Prob (for private ownership)
*/

UCLASS()
class UE5_DONG_PORT_02_API AShop : public ABaseProb
{
	GENERATED_BODY()
	
protected:
	AShop();

	void Active(ABaseHuman* human) override;
	void Deactive(ABaseHuman* human) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Essential")
	TArray<FItemData> SellingItems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Essential")
	float ValueAdjust = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Essential")
	EItemType ShopItemType = EItemType::E_None;

public:
	TArray<FItemData> GetSellingItemData() { return SellingItems; }
	float GetValueAdjust() { return ValueAdjust; }
	EItemType GetItemType() { return ShopItemType; }
};
