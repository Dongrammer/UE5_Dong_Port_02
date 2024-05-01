#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TechniqueSelectHUD.generated.h"

class UCanvasPanel;
class USizeBox;
class UOverlay;
class UImage;
class UHorizontalBox;
class UTechniqueSelectNodeSpace;

UCLASS()
class UE5_DONG_PORT_02_API UTechniqueSelectHUD : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USizeBox> SB_01; // CP_01 Sub

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UOverlay> OL_01; // SB_01 Sub

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UImage> IM_Base; // OL_01 Sub

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UHorizontalBox> HB_01; // OL_01 Sub

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTechniqueSelectNodeSpace> NodeSpace_01;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTechniqueSelectNodeSpace> NodeSpace_02;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTechniqueSelectNodeSpace> NodeSpace_03;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTechniqueSelectNodeSpace> NodeSpace_04;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTechniqueSelectNodeSpace> NodeSpace_05;

public:
	TArray<TObjectPtr<UTechniqueSelectNodeSpace>> NodeSpaces;

public:
	virtual void NativeConstruct() override;
	UFUNCTION()
	void AddNode(UTechniqueNode* node);
};
