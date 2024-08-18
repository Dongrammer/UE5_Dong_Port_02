#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "../Weapon/WeaponData.h"
#include "../Item/ItemData.h"

DECLARE_LOG_CATEGORY_EXTERN(WeaponCompLog, Log, All);

#include "WeaponComponent.generated.h"

class ABaseWeapon;
class ABaseEquip;
class UItemComponent;

/*
	Player와 NPC 모두 가지고 있는 컴포넌트
*/

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5_DONG_PORT_02_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeaponComponent();

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<UItemComponent> ItemComponent;
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadOnly)
	bool bHolding = false;
	
	void SetCurrentWeaponType(EWeaponType type) { CurrentWeaponType = type; }
	FORCEINLINE EWeaponType GetCurrentWeaponType() { return CurrentWeaponType; }
	FORCEINLINE bool GetWeaponHolding() { return bHolding; }

	void SetCurrentWeapon(TObjectPtr<ABaseWeapon> weapon);
private:
	TObjectPtr<ABaseWeapon> CurrentWeapon;
	EWeaponType CurrentWeaponType = EWeaponType::E_Gauntlet;
};
