#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../../Item/ItemData.h"
#include "EquipmentHUD.generated.h"

class USizeBox;
class UButton;
class UImage;
class UEquipSlot;

DECLARE_DELEGATE(FEquipHUDToggle);

UCLASS()
class UE5_DONG_PORT_02_API UEquipmentHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USizeBox> SB_Body;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UButton> BT_Head;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UButton> BT_Exit;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UImage> IM_Base;

public:
	UFUNCTION()
	void HeadPressed();
	UFUNCTION()
	void HeadReleased();
	UFUNCTION()
	void ExitPressed();
	UFUNCTION()
	void MovePosition();
	FVector2D temp;
	bool ShouldMove;

	FEquipHUDToggle DToggle;

	UFUNCTION()
	void ToggleHUD();
	
	void SetSlotImage(EEquipType type, UTexture2D* image, const FLinearColor* color);
	void InitSlotImage(EEquipType type);

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UEquipSlot> Slot_Head;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UEquipSlot> Slot_Chest;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UEquipSlot> Slot_Legs;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UEquipSlot> Slot_Feet;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UEquipSlot> Slot_Hands;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UEquipSlot> Slot_Weapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TMap<EEquipType, TObjectPtr<UEquipSlot>> Slots;
};
