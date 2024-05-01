#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "../Item/ItemData.h"
#include "BaseHuman.generated.h"

class UInventoryComponent;
class UWeaponComponent;
class AHero;

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

protected:
	virtual void BeginPlay() override;

	virtual void CreateCharacter() override;
	virtual void SetCharacterMovement() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UInventoryComponent> InventoryComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWeaponComponent> WeaponComponent;

protected:
	AHero* hero;

public:
	FORCEINLINE AHero* GetHero() { return hero; }
};
