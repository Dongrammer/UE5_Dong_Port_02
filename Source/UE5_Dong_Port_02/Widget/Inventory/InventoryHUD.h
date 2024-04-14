#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryHUD.generated.h"

class UListView;
class UInventorySlotObject;
struct FItemData;

/*
	SlotClass ���� ���� �ʿ�
*/

UCLASS()
class UE5_DONG_PORT_02_API UInventoryHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UListView> ItemList;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UInventorySlotObject> SlotClass;

	// �ߺ��Ǵ� �������� ���� �� ���� �׸��� �߰�
	UFUNCTION()
	void AddItem(const FItemData additem, const int count);

	// �ߺ��Ǵ� �������� ���� �� ������ ����
	UFUNCTION()
	void CountUpItem(const int index, const int count);

public:
	UPROPERTY(VisibleAnywhere, Category = "DataTable")
	UDataTable* OtherDataTable;
	UPROPERTY(VisibleAnywhere, Category = "DataTable")
	UDataTable* EquipmentDataTable;
	UPROPERTY(VisibleAnywhere, Category = "DataTable")
	UDataTable* WeaponDataTable;
};
