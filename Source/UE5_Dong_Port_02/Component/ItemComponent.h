#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Item/ItemData.h"
#include "../Weapon/WeaponData.h"

DECLARE_LOG_CATEGORY_EXTERN(ItemCompLog, Log, All);

#include "ItemComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5_DONG_PORT_02_API UItemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UItemComponent();


protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:
	// 데이터 테이블
	UPROPERTY(VisibleAnywhere, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
	UDataTable* OtherDataTable;
	UPROPERTY(VisibleAnywhere, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
	UDataTable* EquipmentDataTable;
	UPROPERTY(VisibleAnywhere, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
	UDataTable* WeaponDataTable;

private:
	// 캐싱 데이터
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
	FName GetItemName(FItemData item);
	EEquipType GetEquipType(FItemData item) { return CachedEquipmentItems.Find(item.ItemID)->EquipType; }
	TSubclassOf<ABaseItem> GetEquipItemClass(FItemData item) { return CachedEquipmentItems.FindRef(item.ItemID).ItemClass; }
	FEquipmentItem GetEquipmentDataTable(FItemData item);
	EWeaponType GetWeaponType(FItemData item) { return CachedEquipmentItems.FindRef(item.ItemID).WeaponType; }

};
