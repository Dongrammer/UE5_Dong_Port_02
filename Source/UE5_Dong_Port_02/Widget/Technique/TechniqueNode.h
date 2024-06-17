#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "../../Action/ActionData.h"

#include "TechniqueNode.generated.h"

class USizeBox;
class UOverlay;
class UImage;
class UButton;
class UTextBlock;
class ABaseAction;

/*
	노드 추가-> 레벨 지정
*/

DECLARE_MULTICAST_DELEGATE_OneParam(FNodeSelect, UTechniqueNode*);

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
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UImage> IM_Selected; // Ol_Base Sub
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UImage> IM_Lock; // Ol_Base Sub


public:
	FNodeSelect DNodeSelect;
	bool bNodeSelected = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FActionData ActionData;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bActive;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	EActionPassiveType PassiveType;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	uint8 NodeLevel = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	uint8 MaxNodeLevel = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	uint8 RequiredTP = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText NodeName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText NodeDescription;

	// Check Require
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UTechniqueNode> RequireNode;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	uint8 RequireNodeLevel = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bUnlock = false;

public:
	void ConnectRequireNode();
	UFUNCTION()
	void CheckRequireNode();
	void Unlock();

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void Bt_Main_Clicked();

	void ActiveNode();
	void AddNodeLevel();
	void NodeLevelSetting();
	void SelectedIMVisible(bool visible);

	FORCEINLINE FActionData GetAction() { return ActionData; }
	FORCEINLINE EActionPassiveType GetPassiveType() { return PassiveType; }
	FORCEINLINE bool GetActive() { return bActive; }
	FORCEINLINE uint8 GetNodeLevel() { return NodeLevel; }
	FORCEINLINE uint8 GetMaxNodeLevel() { return MaxNodeLevel; }
	FORCEINLINE TObjectPtr<UImage> GetImage() { return Im_Base; }
};
