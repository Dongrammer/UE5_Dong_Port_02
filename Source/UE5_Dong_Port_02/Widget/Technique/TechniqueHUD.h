#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "TechniqueNodeHUD.h"
#include "TechniqueSelectHUD.h"

#include "TechniqueHUD.generated.h"

class USizeBox;
class UTextBlock;

/*
	NextHUD, PrevHUD, and ThisHUD must be defined in the blueprint constructor.
*/

UCLASS(Blueprintable)
class UE5_DONG_PORT_02_API UTechniqueHUD : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USizeBox> NodeHUDBox;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTechniqueNodeHUD> NodeHUD;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USizeBox> SelectHUDBox;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTechniqueSelectHUD> SelectHUD;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UButton> Bt_NextHUD;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UButton> Bt_PrevHUD;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTextBlock> TB_ThisHUD;

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void MoveToNextHUD();
	UFUNCTION()
	void MoveToPrevHUD();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UTechniqueHUD> NextHUD;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UTechniqueHUD> PrevHUD;
};
