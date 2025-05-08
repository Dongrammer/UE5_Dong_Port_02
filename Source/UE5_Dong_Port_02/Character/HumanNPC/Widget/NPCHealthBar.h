#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NPCHealthBar.generated.h"

class UCanvasPanel;
class USizeBox;
class UProgressBar;

UCLASS()
class UE5_DONG_PORT_02_API UNPCHealthBar : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void SetHealthPercent(float percent);
	UFUNCTION()
	void SetBackHealthBar();
	
private:
	/*UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), meta = (BindWidget))
	TObjectPtr<UCanvasPanel> CP_01;*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), meta = (BindWidget))
	TObjectPtr<USizeBox> SB_01;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), meta = (BindWidget))
	TObjectPtr<UProgressBar> PB_Health;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), meta = (BindWidget))
	TObjectPtr<UProgressBar> PB_BackHealth;

	FTimerHandle backhandle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float Reductiontime = 1.0f; // ÃÑ °¨¼Ò ½Ã°£
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float ReductionSoftness = 20.0f;
	float amount = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), meta = (BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation> VisibleAnim;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), meta = (BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation> InvisibleAnim;

public:
	void PlayVisibleAnim();
	void PlayInvisibleAnim();
};
