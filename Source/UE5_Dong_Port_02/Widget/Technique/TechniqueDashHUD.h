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
	TObjectPtr<UTechniqueDashNode> PrevNode; // ���� ���
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTechniqueDashNode> CurrNode; // ���� ���
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTechniqueDashNode> NextNode; // ���� ���

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

	// Technique Component�� �뽬(�� �׼�)�� Ptr�� ������ ���� �ʱ� ������ (= ��忡 NodeInfo�� �ۼ��� �� ����, DashAction���� NodeInfo�� ������ �� ����.) �߰�
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SetNodeInfo();
};
