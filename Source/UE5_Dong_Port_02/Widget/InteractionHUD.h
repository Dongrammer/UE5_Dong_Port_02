#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionHUD.generated.h"

UENUM(BlueprintType)
enum class EInteractionHUDType : uint8
{
	E_None UMETA(Hidden),
	E_Get UMETA(DisplayName = "Get"),
	E_Use UMETA(DisplayName = "Use"),
	E_Trade UMETA(DisplayName = "Trade"),
	E_Max UMETA(Hidden)
};

class UCanvasPanel;
class USizeBox;
class UTextBlock;
class UVerticalBox;
class UWidgetSwitcher;

UCLASS()
class UE5_DONG_PORT_02_API UInteractionHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCanvasPanel> CP_01;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USizeBox> SB_Body;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UVerticalBox> VB_01;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWidgetSwitcher> WS_01;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTextBlock> TB_Use;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTextBlock> TB_Get;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTextBlock> TB_Name;

public:
	//void SetName(FName name);
	void SetPosition(FVector2D position);

	void ActiveWidget(EInteractionHUDType type, FName name);
	void DeactiveWidget();
	void ChangeName(FName name);
};
