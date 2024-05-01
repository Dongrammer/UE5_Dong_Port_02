#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TechniqueSelectNodeSpace.generated.h"

class USizeBox;
class UOverlay;
class UListView;
class UImage;
class UButton;

class UTechniqueNode;

DECLARE_MULTICAST_DELEGATE_TwoParams(FSelectAction, TSubclassOf<ABaseAction>, uint8);

UCLASS()
class UE5_DONG_PORT_02_API UTechniqueSelectNodeSpace : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USizeBox> SB_01; // Top

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UOverlay> OL_01; // SB_01 Sub

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UListView> ActionList; // OL_01 Sub

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> IM_Main; // OL_01 Sub

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UButton> Bt_Main; // OL_01 Sub

public:
	virtual void NativeConstruct() override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	UFUNCTION()
	void AddNode(UTechniqueNode* node);

	UFUNCTION()
	void MainButtonClicked();

	UFUNCTION()
	void SelectNodeDelegate(TSubclassOf<ABaseAction> action, UImage* image);

	TObjectPtr<UListView> GetActionList() { return ActionList; }

	FSelectAction DSelectAction;

	uint8 SpaceNum = 0;
};
