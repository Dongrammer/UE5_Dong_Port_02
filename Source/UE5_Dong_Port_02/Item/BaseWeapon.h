#pragma once

#include "CoreMinimal.h"
#include "../Item/BaseEquip.h"
#include "BaseWeapon.generated.h"

class UCapsuleComponent;

UCLASS()
class UE5_DONG_PORT_02_API ABaseWeapon : public ABaseEquip
{
	GENERATED_BODY()

public:
	ABaseWeapon();

	virtual void BeginPlay() override;

	EWeaponType GetWeaponType() { return WeaponType; }
	TObjectPtr<UCapsuleComponent> GetWeaponCapsule() { return WeaponCapsule; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TObjectPtr<UCapsuleComponent> WeaponCapsule;

	EWeaponType WeaponType = EWeaponType::E_None;
};
