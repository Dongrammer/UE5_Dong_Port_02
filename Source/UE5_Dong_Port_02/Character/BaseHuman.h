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

protected:
	virtual void BeginPlay() override;

	virtual void CreateCharacter() override;
	virtual void SetCharacterMovement() override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UInventoryComponent> InventoryComponent;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UWeaponComponent> WeaponComponent;

protected:
	AHero* hero;

public:
	FORCEINLINE AHero* GetHero() { return hero; }
};
