#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../../Item/ItemData.h"
#include "InventorySlotObject.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FItemCountUp, int);
DECLARE_MULTICAST_DELEGATE_OneParam(FItemUse, FItemData);
DECLARE_MULTICAST_DELEGATE_OneParam(FItemClick, FItemData);

UCLASS(Blueprintable)
class UE5_DONG_PORT_02_API UInventorySlotObject : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly)
	FItemData ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FItemDataTableBase ItemDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int ItemCount;

	/* ========== Delegate ========== */
	// Count Delegate
	FItemCountUp DItemCountUp;
	// Use Delegate
	FItemUse DItemUse;
	// Left Click Delegate
	FItemClick DItemClick;

	void CountUp(int count);
};
