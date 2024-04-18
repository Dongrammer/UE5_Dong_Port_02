#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Logging/LogMacros.h"
#include "../../Item/ItemData.h"
#include "InventorySlot.generated.h"

class UImage;
class UTextBlock;

UCLASS()
class UE5_DONG_PORT_02_API UInventorySlot : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	FItemData ItemData;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> ItemImage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_ItemName;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_ItemWeight;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_ItemCount;

public:
	void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	
	UFUNCTION()
	void SetCountText(int count);
};
