#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../../Item/ItemData.h"
#include "InventorySlotObject.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FItemCountUp, int);

UCLASS(Blueprintable)
class UE5_DONG_PORT_02_API UInventorySlotObject : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FItemDataTableBase ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int ItemCount;

	// Count Delegate
	FItemCountUp DItemCountUp;

	void CountUp(int count);
};
