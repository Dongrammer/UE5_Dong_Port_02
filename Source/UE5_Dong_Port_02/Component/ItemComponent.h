#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Item/ItemData.h"

DECLARE_LOG_CATEGORY_EXTERN(ItemCompLog, Log, All);

#include "ItemComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5_DONG_PORT_02_API UItemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UItemComponent();

	//static UItemComponent* GetInstance();

private:
	//static UItemComponent* Instance;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:
	UPROPERTY(VisibleAnywhere, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
	UDataTable* OtherDataTable;
	UPROPERTY(VisibleAnywhere, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
	UDataTable* EquipmentDataTable;
	UPROPERTY(VisibleAnywhere, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
	UDataTable* WeaponDataTable;

private:
	void CachingDataTable();

	UPROPERTY(VisibleAnywhere, Category = "CachedItems", meta = (AllowPrivateAccess = "true"))
	TMap<FName, FOtherItem> CachedOtherItems;
	UPROPERTY(VisibleAnywhere, Category = "CachedItems", meta = (AllowPrivateAccess = "true"))
	TMap<FName, FEquipmentItem> CachedEquipmentItems;
	UPROPERTY(VisibleAnywhere, Category = "CachedItems", meta = (AllowPrivateAccess = "true"))
	TMap<FName, FWeaponItem> CachedWeaponItems;

	UPROPERTY(VisibleAnywhere, Category = "Rarity", meta = (AllowPrivateAccess = "true"))
	TMap<ERarity, FLinearColor> RarityColor;

	FLinearColor s;
public:
	void SetRarityColor();
	const FLinearColor* GetRarityColor(ERarity rarity);
	float GetItemWeight(FItemData item);
	FItemDataTableBase GetDataTableBase(FItemData item);
	FEquipmentItem GetEquipmentDataTable(FItemData item);

};
