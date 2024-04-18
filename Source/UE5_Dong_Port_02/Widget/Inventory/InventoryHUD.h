#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryHUD.generated.h"

class UListView;
class UInventorySlotObject;
class UTextBlock;
class UButton;
class USizeBox;
struct FItemDataTableBase;
struct FItemData;

DECLARE_DELEGATE(FInventoryExit);
/*
	SlotClass ���� ���� �ʿ�
*/

UCLASS()
class UE5_DONG_PORT_02_API UInventoryHUD : public UUserWidget
{
	GENERATED_BODY()
	
private:
	APlayerController* PlayerController;

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION()
	void HeadPressed();
	UFUNCTION()
	void HeadReleased();
	UFUNCTION()
	void MovePosition();
	FVector2D temp;
	bool ShouldMove;

	UFUNCTION()
	void ExitPressed();
	FInventoryExit DExit;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UListView> ItemList;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UInventorySlotObject> SlotClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<USizeBox> SB_Body;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_Weight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> Button_Head;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> Button_Exit;

	// When ItemComponent Adding a new Item
	UFUNCTION()
	void AddItem(const FItemDataTableBase additem, const int count);

	// When ItemComponent find the same item
	UFUNCTION()
	void CountUpItem(const int index, const int count);

	void SetTextWeight(float max, float current);
};
