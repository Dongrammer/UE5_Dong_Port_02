#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Item/ItemData.h"

DECLARE_LOG_CATEGORY_EXTERN(EquipComponentLog, Log, All);

#include "EquipComponent.generated.h"

class UEquipmentHUD;
class ABaseHuman;
class ABaseEquip;
class UItemComponent;
class UWeaponComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5_DONG_PORT_02_API UEquipComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UEquipComponent();
	TObjectPtr<ABaseHuman> OwnerCharacter;

protected:
	virtual void BeginPlay() override;
	void InitEquipParts();
	
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/* ==================== HUD ==================== */ 
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UEquipmentHUD> EquipmentHUD;
	UPROPERTY()
	TObjectPtr<UItemComponent> ItemComponent;
	UPROPERTY()
	TObjectPtr<UWeaponComponent> WeaponComponent;

public:
	void GetWeaponComponent(TObjectPtr<UWeaponComponent> weaponcomponent) { WeaponComponent = weaponcomponent; }
	void ToggleHUD();
	void InitEquipmentHUD(TObjectPtr<UEquipmentHUD> hud);

	/* ==================== Equipment ==================== */
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TMap<EEquipType, FItemData> EquipParts;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<EEquipType, TObjectPtr<ABaseEquip>> EquipmentParts;

	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FItemData Head;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FItemData Chest;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FItemData Legs;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FItemData Feet;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FItemData Hands;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FItemData Weapon;*/

	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ABaseEquip> HeadEquipment;*/

public:
	void Equip(FItemData item);
	void UnEquip(EEquipType type);
	void SpawnAndAttach(EEquipType type);
	void HandleWeapon(bool equip);

	void HUDImageSetting(EEquipType type);
};
