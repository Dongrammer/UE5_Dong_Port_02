#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainHUD.generated.h"

class UCanvasPanel;

class UEquipmentHUD;
class UInventoryHUD;

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

public:
	void InitHUD(TObjectPtr<UEquipmentHUD> equipHUD, TObjectPtr<UInventoryHUD> invenHUD);
	FORCEINLINE TObjectPtr<UInventoryHUD> GetInvenHUD() { return InvenHUD; }
	FORCEINLINE TObjectPtr<UEquipmentHUD> GetEquipHUD() { return EquipHUD; }

	void ToggleEquipHUD();
	void ToggleInvenHUD();

	bool CheckHUDsVisibility(); // HUD가 하나라도 열려있는가?
};
