#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SoulHUD.generated.h"

class UCanvasPanel;
class UProgressBar;

UCLASS()
class UE5_DONG_PORT_02_API USoulHUD : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCanvasPanel> CP_01; // Top
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UProgressBar> PB_SoulGage;
	
public:
	void SetSouleGage(float MaxGage, float CurrGage);

};
