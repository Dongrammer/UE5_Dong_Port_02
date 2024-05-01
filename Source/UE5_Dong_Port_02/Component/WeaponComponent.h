#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "../Weapon/WeaponData.h"

#include "WeaponComponent.generated.h"

/*
	Player�� NPC ��� ������ �ִ� ������Ʈ
*/

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5_DONG_PORT_02_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeaponComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadOnly)
	bool bHolding = false;
	
	FORCEINLINE EWeaponType GetCurrentWeaponType() { return CurrentWeaponType; }
	FORCEINLINE bool GetWeaponHolding() { return bHolding; }

private:
	EWeaponType CurrentWeaponType = EWeaponType::E_Gauntlet;
};
