#pragma once

#include "CoreMinimal.h"
#include "Item/BaseItem.h"
#include "BaseWeapon.generated.h"

UCLASS()
class UE5_DONG_PORT_02_API ABaseWeapon : public ABaseItem
{
	GENERATED_BODY()

public:
	ABaseWeapon();

	virtual void BeginPlay() override;
	virtual void DataTableSetting() override;
	void SetEquipment();
};
