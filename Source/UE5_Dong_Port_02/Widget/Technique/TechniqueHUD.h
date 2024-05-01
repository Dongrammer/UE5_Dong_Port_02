#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "TechniqueNodeHUD.h"
#include "TechniqueSelectHUD.h"

#include "TechniqueHUD.generated.h"

class USizeBox;
class UTextBlock;
class UButton;
enum class EWeaponType : uint8;

/*
	NextHUD, PrevHUD, and ThisHUD must be defined in the blueprint constructor.
*/

UCLASS(Blueprintable)
class UE5_DONG_PORT_02_API UTechniqueHUD : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTextBlock> TB_ThisHUD;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USizeBox> NodeHUDBox;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USizeBox> SelectHUDBox;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTextBlock> TB_TP;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true") , meta = (BindeWidgetType = "UTechniqueNodeHUD"))
	TObjectPtr<UTechniqueNodeHUD> NodeHUD;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTechniqueSelectHUD> SelectHUD;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UButton> Bt_NextHUD;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UButton> Bt_PrevHUD;


public:
	virtual void NativeConstruct() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EWeaponType HUDWeaponType;
	void SetWeaponType(EWeaponType type) { HUDWeaponType = type; }

	void SettingTP(uint8 currentTP, uint8 MaxTP);
};
