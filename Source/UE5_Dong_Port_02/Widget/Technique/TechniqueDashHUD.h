#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "../../Action/ActionData.h"

DECLARE_LOG_CATEGORY_EXTERN(TechniqueDashHUDLog, Log, All);

#include "TechniqueDashHUD.generated.h"

class UTechniqueDashNode;
class ABaseDash;

class USizeBox;
class UHorizontalBox;
class UButton;
class UImage;

DECLARE_MULTICAST_DELEGATE_OneParam(FDashHUDSelectNode, EDashAction);

UCLASS()
class UE5_DONG_PORT_02_API UTechniqueDashHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void InitHUD(TArray<EDashAction> dashes);

private:
	virtual void NativeConstruct() override;

	TArray<EDashAction> Dashes;
	EDashAction PrevDash;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EDashAction CurrDash;
	EDashAction NextDash;

	void SetImage();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Essential")
	TMap<EDashAction, TObjectPtr<UTexture2D>> DashImages;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTechniqueDashNode> PrevNode; // 이전 노드
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTechniqueDashNode> CurrNode; // 현재 노드
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTechniqueDashNode> NextNode; // 다음 노드

	FDashHUDSelectNode DSelectNode;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> BT_Info;
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USizeBox> SB_01;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UHorizontalBox> HB_01;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UImage> IM_InfoSelected;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UButton> BT_Next;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UButton> BT_Prev;

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void PlayNextAnimation();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void PlayPrevAnimation();

	UFUNCTION()
	void CallNext();
	UFUNCTION()
	void CallPrev();
	
	UFUNCTION()
	FNodeInfoData GetNodeInfoData();

	void ClickImageVisible(bool visible);

	// Technique Component가 대쉬(와 액션)의 Ptr을 가지고 있지 않기 때문에 (= 노드에 NodeInfo를 작성할 수 없음, DashAction에서 NodeInfo를 가져올 수 없음.) 추가
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SetNodeInfo();
};
