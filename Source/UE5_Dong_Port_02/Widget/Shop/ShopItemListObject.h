#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../../Item/ItemData.h"
#include "ShopItemListObject.generated.h"

DECLARE_DELEGATE_OneParam(FClickSlot, UShopItemListObject*);
//DECLARE_DELEGATE_OneParam(FItemCountUp, int);
DECLARE_DELEGATE(FShopItemCountUp);
DECLARE_DELEGATE(FShopItemCountMultValue);

UCLASS()
class UE5_DONG_PORT_02_API UShopItemListObject : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	FItemData ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FItemDataTableBase ItemDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int ItemCount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Value;

	FClickSlot DClickSlot;
	FShopItemCountUp DItemCountUp;
	FShopItemCountMultValue DCountMultValue; // ToSellList, ToBuyList에서만 사용

	void CountUp(int count);
	void ValueMultCount();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int CountMultValue = 0;
};
