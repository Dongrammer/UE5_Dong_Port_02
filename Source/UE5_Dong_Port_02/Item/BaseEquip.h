#pragma once

#include "CoreMinimal.h"
#include "Item/BaseItem.h"
#include "BaseEquip.generated.h"

UCLASS()
class UE5_DONG_PORT_02_API ABaseEquip : public ABaseItem
{
	GENERATED_BODY()
	
public:
	ABaseEquip();

	virtual void BeginPlay() override;
	//virtual void DataTableSetting() override;
	void SetEquipment();

//public:
//	UPROPERTY(VisibleAnywhere, Category = "DataTable")
//	EEquipType EquipType;
//	UPROPERTY(VisibleAnywhere, Category = "DataTable")
//	TMap<EEquipStatus, int> EquipStatus;
};
