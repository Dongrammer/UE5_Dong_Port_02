#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Item/ItemData.h"

DECLARE_LOG_CATEGORY_EXTERN(InventoryCompLog, Log, All);

#include "InventoryComponent.generated.h"

class UItemComponent;
class ABaseHuman;
class ABaseItem;
class UInventoryHUD;
class UInventoryContextMenu;
struct FItemDataTableBase;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5_DONG_PORT_02_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent();
	void SetItemComponent(TObjectPtr<UItemComponent> comp) { ItemComponent = comp; }

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION()
	bool CheckWeight(float itemweight);
	void GetItems(const FItemData itemdata, const int count);
	TArray<FItem> GetHaveItems() { return Items; }
	int GetCurrentGold() { return CurrentGold; }
	void GetGold(int gold) { CurrentGold += gold; }
	bool CheckCanGetItem(FItemData data);

protected:
	UPROPERTY(VisibleAnywhere)
	TArray<FItem> Items;
	UPROPERTY(VisibleAnywhere, Category = "Weight")
	float MaxInvenWeight = 100.0;
	UPROPERTY(VisibleAnywhere, Category = "Weight")
	float CurrentWeight = 0;
	UPROPERTY(VisibleAnywhere, Category = "Money")
	int CurrentGold = 0;

public:
	ABaseHuman* Owner;
	TObjectPtr<UInventoryHUD> InvenHUD;
	void InitInvenHUD(TObjectPtr<UInventoryHUD> hud); // Used Only for Hero
	TObjectPtr<UInventoryContextMenu> ContextMenu;
	void InitContextMenu(TObjectPtr<UInventoryContextMenu> menu);

	void ItemUse(FItemData item);
	void ItemClick(FItemData item);
	void SetWeight(float weight);
	void EquipItem(FItemData item);
	
	FORCEINLINE float GetMaxWeight() { return MaxInvenWeight; }
	FORCEINLINE float GetCurrentWeight() { return CurrentWeight; }
	/*void SetFocusHUD();
	void SetFocusInit();*/

private:
	UItemComponent* ItemComponent;
};
