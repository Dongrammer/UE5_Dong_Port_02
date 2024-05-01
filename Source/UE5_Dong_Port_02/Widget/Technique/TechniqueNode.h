#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TechniqueNode.generated.h"

class USizeBox;
class UOverlay;
class UImage;
class UButton;
class ABaseAction;
class UTextBlock;
class UTechniqueHUD;

/*
	노드 추가-> 레벨 지정
*/

DECLARE_MULTICAST_DELEGATE_OneParam(FNodeSelect, TObjectPtr<UTechniqueNode>);

UCLASS()
class UE5_DONG_PORT_02_API UTechniqueNode : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USizeBox> SB_Base; // Top
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UOverlay> Ol_Base; // SB_Base Sub
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UImage> Im_Base; // Ol_Base Sub
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTextBlock> Tx_Level; // Ol_Base Sub
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UButton> Bt_Main; // Ol_Base Sub


public:
	FNodeSelect DNodeSelect;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<ABaseAction> Action;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	uint8 ActionLevel = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	uint8 MaxActionLevel = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	uint8 RequiredTP = 1;

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void Bt_Main_Clicked();

	UFUNCTION()
	void ActiveNode();
	
	UFUNCTION()
	void AddActionLevel();
	void ActionLevelSetting();

	TSubclassOf<ABaseAction> GetAction() { return Action; }
	uint8 GetActionLevel() { return ActionLevel; }
	uint8 GetMaxActionLevel() { return MaxActionLevel; }
	TObjectPtr<UImage> GetImage() { return Im_Base; }
};
