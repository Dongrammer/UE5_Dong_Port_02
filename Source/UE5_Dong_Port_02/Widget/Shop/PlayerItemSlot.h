#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "../../Item/ItemData.h"

#include "PlayerItemSlot.generated.h"

class UImage;
class UTextBlock;
class UBorder;
class UShopItemListObject;

UCLASS()
class UE5_DONG_PORT_02_API UPlayerItemSlot : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TObjectPtr<UShopItemListObject> item;

	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FItemData ItemData;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FItemDataTableBase ItemDataTable;*/

	UPROPERTY(meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UImage> IM_ItemImage;
	UPROPERTY(meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTextBlock> TB_ItemName;
	UPROPERTY(meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTextBlock> TB_ItemCount;
	UPROPERTY(meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTextBlock> TB_Value;

	UPROPERTY(meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBorder> BO_Hovered;
public:
	void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	//virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	UFUNCTION()
	void SetCountText();
	UFUNCTION()
	void SetValueText(); // ToSellList, ToBuyList에서만 사용

	bool bIsMouseOn = false;
};
