#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "../../Action/ActionData.h"

#include "TechniqueNode.generated.h"

class USizeBox;
class UVerticalBox;
class UOverlay;
class UImage;
class UButton;
class UTextBlock;
class ABaseAction;
class UTechniqueNodeBase;
class AHero;
/*
	노드 추가-> 레벨 지정
*/

DECLARE_MULTICAST_DELEGATE_OneParam(FNodeSelect, UTechniqueNode*);
DECLARE_MULTICAST_DELEGATE_OneParam(FConnectRequireNode, UTechniqueNode*);

UCLASS()
class UE5_DONG_PORT_02_API UTechniqueNode : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USizeBox> SB_Base; // Top
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UVerticalBox> VB_Base; // SB_Base Sub
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTextBlock> Tx_NodeName; // VB_Base Sub


public:
	TObjectPtr<AHero> hero;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tech", meta = (ExposeOnSpawn = "true", DisplayThumbnail = "true"))
	TObjectPtr<UTechniqueNodeBase> TechNode;

	FNodeSelect DNodeSelect;
	bool bNodeSelected = false;


public:
	UTechniqueNodeBase* GetTechNode();
	void NodeInit();
	void NodeRefresh(uint8 curLevel);

	// Check Require
	//UFUNCTION()
	//void CheckRequirements();
	void Unlock();
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bUnlock = false;
	FConnectRequireNode DConnectRequireNode;

public:
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;

	UFUNCTION()
	void Bt_Main_Clicked();

	void ActiveNode();
	//void AddNodeLevel();
	void NodeLevelSetting(uint8 curLevel);
	void SelectedIMVisible(bool visible);
	/*
	///////////////////////////////////////////////////////////////////
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FActionData ActionData;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bActive;


	FORCEINLINE FActionData GetAction() { return ActionData; }
	FORCEINLINE EActionPassiveType GetPassiveType() { return PassiveType; }
	FORCEINLINE bool GetActive() { return bActive; }
	FORCEINLINE uint8 GetNodeLevel() { return NodeLevel; }
	FORCEINLINE uint8 GetMaxNodeLevel() { return MaxNodeLevel; }
	FORCEINLINE TObjectPtr<UImage> GetImage() { return Im_Base; }
	*/
};