#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TechniqueDashNode.generated.h"

class USizeBox;
class UOverlay;
class UImage;
// class UButton;

UCLASS()
class UE5_DONG_PORT_02_API UTechniqueDashNode : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USizeBox> SB_Base; // Top
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UOverlay> OL_Base; // SB_Base Sub
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UImage> IM_Base; // Ol_Base Sub
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	//TObjectPtr<UButton> Bt_Main; // Ol_Base Sub

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText NodeName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText NodeDescription;

public:
	void SetImage(TObjectPtr<UTexture2D> texture);
};
