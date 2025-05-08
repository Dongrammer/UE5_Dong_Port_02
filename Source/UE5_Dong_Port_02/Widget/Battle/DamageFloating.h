#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DamageFloating.generated.h"

class USizeBox;
class UTextBlock;

UCLASS()
class UE5_DONG_PORT_02_API UDamageFloating : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USizeBox> SB_Body;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTextBlock> TB_Damage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidgetAnim), meta = (AllowprivateAccess = "true"), Transient)
	TObjectPtr<UWidgetAnimation> AN_Floating;

public:
	void FloatingWidget(int damage);

	FWidgetAnimationDynamicEvent DFinishEvent;

	UFUNCTION()
	void DestroythisWidget();
};
