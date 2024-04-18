#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TechniqueNodeHUD.generated.h"

class UImage;
class UButton;
class UCanvasPanel;

UCLASS()
class UE5_DONG_PORT_02_API UTechniqueNodeHUD : public UUserWidget
{
	GENERATED_BODY()
	
private:
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	//TObjectPtr<UButton> Button_Background;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UImage> Image_Background;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCanvasPanel> Canvas;

private:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	FReply NativeOnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

private:
	//bool bBackgroundHovered;
	//UFUNCTION()
	//void BackgroundHovered();
	//UFUNCTION()
	//void BackgroundUnHovered();
};
