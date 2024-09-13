#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "Component/WeaponComponent.h"
#include "../Item/ItemData.h"
#include "BaseHuman.generated.h"

class UInventoryComponent;
class UEquipComponent;
class AHero;
class ABuilding;

UCLASS()
class UE5_DONG_PORT_02_API ABaseHuman : public ABaseCharacter
{
	GENERATED_BODY()

public:
	ABaseHuman();

	bool bInteraction = false;
	UFUNCTION()
	virtual void GetItems(FItemData item, int count);
	virtual bool CheckItemWeight(float itemweight);
	virtual TObjectPtr<UWeaponComponent> GetWeaponComponent() { return WeaponComponent; }
	virtual bool GetWeaponHolding();
	virtual void SetCurrentWeaponType(EWeaponType type);

protected:
	virtual void BeginPlay() override;

	virtual void CreateCharacter() override;
	virtual void SetCharacterMovement() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UInventoryComponent> InventoryComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWeaponComponent> WeaponComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UEquipComponent> EquipComponent;

protected:
	AHero* hero;

public:
	FORCEINLINE AHero* GetHero() { return hero; }

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float PlayRate = 1.0f;
	/* PlayRate : BaseAction과 Movement에 영향 */

public:
	void SetPlayRate(float playrate);
	FORCEINLINE float GetPlayRate() { return PlayRate; }


	/* ========== Building ========== */
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<ABuilding> CurrentBuilding;

public:
	UFUNCTION()
	void SetCurrentBuilding(ABuilding* building) { CurrentBuilding = building; }

	bool IsInBuilding() { return !(CurrentBuilding == nullptr); }
	TObjectPtr<ABuilding> GetCurrentBuilding() { return CurrentBuilding; }
};
