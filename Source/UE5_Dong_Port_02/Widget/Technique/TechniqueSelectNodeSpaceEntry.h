#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"

#include "../../Action/ActionData.h"

#include "TechniqueSelectNodeSpaceEntry.generated.h"

class USizeBox;
class UImage;
class UButton;
class UTechniqueSelectNodeObject;

UCLASS()
class UE5_DONG_PORT_02_API UTechniqueSelectNodeSpaceEntry : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USizeBox> SB_01; // Top

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UImage> IM_Base;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UButton> BT_Main;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FActionData action;

	// Save NodeObject For Delegate
	TObjectPtr<UTechniqueSelectNodeObject> node;

public:
	virtual void NativeConstruct() override;
	void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	UFUNCTION()
	void MainButtonClicked();
};
