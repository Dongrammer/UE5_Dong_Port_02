#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../../Item/ItemData.h"
#include "ShopHUD.generated.h"

class UCanvasPanel;
class USizeBox;
class UButton;
class UListView;
class UItemComponent;
class UImage;
class UTextBlock;
class AHero;

DECLARE_DELEGATE(FShopHUDToggle);

UCLASS()
class UE5_DONG_PORT_02_API UShopHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	void ActiveHUD(TArray<FItem> PlayerItems, TArray<FItemData> SellingItems, float AdjValue, EItemType shopitemtype);
	void SetOwnerPlayer(AHero* player) { OwnerPlayer = player; }
	
protected:
	TObjectPtr<UItemComponent> ItemComponent;
	TObjectPtr<AHero> OwnerPlayer;
	float ValueAdjust = 1.0f;
	EItemType ShopItemType = EItemType::E_None;
	float ToSellRandomValueMin = 0.6;
	float ToSellRandomValueMax = 1.2f;

	UFUNCTION()
	void ExitPressed();
	UFUNCTION()
	void TradePressed();

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCanvasPanel> CP_01;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USizeBox> SB_ShopItems;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UListView> LV_ShopItemList;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USizeBox> SB_ToBuyItems;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UListView> LV_ToBuyItemList;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USizeBox> SB_ToSellItems;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UListView> LV_ToSellItemList;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USizeBox> SB_PlayerItems;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UListView> LV_PlayerItemList;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UImage> IM_PlayerGold;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTextBlock> TB_PlayerGold;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UImage> IM_Gold;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTextBlock> TB_MinTradeGold; 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTextBlock> TB_MaxTradeGold;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UButton> Bt_Trade;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UButton> Bt_Exit;

public:
	UFUNCTION()
	void PlayerItemListClick(UShopItemListObject* object);
	UFUNCTION()
	void ToSellItemListClick(UShopItemListObject* object);
	UFUNCTION()
	void ToBuyItemListClick(UShopItemListObject* object);
	UFUNCTION()
	void ShopItemListClick(UShopItemListObject* object);

	FShopHUDToggle DShopHUDToggle;

	void SetTradeGold(int value);
	void SetTradeGoldNotType(int value);
	int MinTradeGold = 0;
	int MaxTradeGold = 0;
	int SetRandomValue(int val);
	
	// Widget Animation
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowprivateAccess = "true"))
	TObjectPtr<USizeBox> SB_NoMoney;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowprivateAccess = "true"))
	TObjectPtr<UTextBlock> TB_NoMoney;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidgetAnim), meta = (AllowprivateAccess = "true"), Transient)
	TObjectPtr<UWidgetAnimation> AN_NoMoney;
};
