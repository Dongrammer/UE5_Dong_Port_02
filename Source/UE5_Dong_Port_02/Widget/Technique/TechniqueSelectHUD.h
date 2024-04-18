#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TechniqueSelectHUD.generated.h"

class UImage;

UCLASS()
class UE5_DONG_PORT_02_API UTechniqueSelectHUD : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UImage> Image_Background;
};
