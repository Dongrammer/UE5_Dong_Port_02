#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainHUD.generated.h"

class UCanvasPanel;

class UEquipmentHUD;
class UInventoryHUD;
class UStatusHUD;

class UInventoryContextMenu;

UCLASS()
class UE5_DONG_PORT_02_API UMainHUD : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCanvasPanel> CP_01;

	// HUDs
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UEquipmentHUD> EquipHUD;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInventoryHUD> InvenHUD;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStatusHUD> StatusHUD;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInventoryContextMenu> ContextMenu;

public:
	virtual void NativeConstruct() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	void InitHUD(TObjectPtr<UEquipmentHUD> equipHUD, TObjectPtr<UInventoryHUD> invenHUD, TObjectPtr<UStatusHUD> statusHUD);
	FORCEINLINE TObjectPtr<UInventoryHUD> GetInvenHUD() { return InvenHUD; }
	FORCEINLINE TObjectPtr<UEquipmentHUD> GetEquipHUD() { return EquipHUD; }
	FORCEINLINE TObjectPtr<UStatusHUD> GetStatusHUD() { return StatusHUD; }
	FORCEINLINE TObjectPtr<UInventoryContextMenu> GetContextMenu() { return ContextMenu; }

	void ToggleEquipHUD();
	void ToggleInvenHUD();
	void ToggleStatusHUD();

	bool CheckHUDsVisibility(); // HUD가 하나라도 열려있는가?
};
