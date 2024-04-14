#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Item/ItemData.h"
#include "InventoryComponent.generated.h"

class ABaseHuman;
class ABaseItem;
class UInventoryHUD;

USTRUCT(BlueprintType)
struct FItem
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Essential", meta = (AllowPrivateAccess = "true"))
	FItemData ItemData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Essential", meta = (AllowPrivateAccess = "true"), meta = (ClampMin = "0"))
	int count = 0;

};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5_DONG_PORT_02_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION()
	bool CheckWeight(float itemweight);
	void GetItems(const FItemData itemdata, const int count);

protected:
	TArray<FItem> Items;
	float MaxInvenWeight = 100.0;
	float CurrentWeight = 0;

public:
	ABaseHuman* Owner;
	TObjectPtr<UInventoryHUD> InvenHUD;
	
};
