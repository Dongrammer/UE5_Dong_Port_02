#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../../Item/ItemData.h"
#include "InventorySlotObject.generated.h"

UCLASS(Blueprintable)
class UE5_DONG_PORT_02_API UInventorySlotObject : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FItemDataTableBase ItemData;
};
