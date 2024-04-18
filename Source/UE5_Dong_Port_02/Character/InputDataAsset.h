#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputDataAsset.generated.h"

class UInputAction;

UCLASS()
class UE5_DONG_PORT_02_API UInputDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	/* ==================== Movement ==================== */

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveInput;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* LookInput;

	/* ==================== Action ==================== */

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Action", meta = (AllowPrivateAccess = "true"))
	UInputAction* Interaction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Action", meta = (AllowPrivateAccess = "true"))
	UInputAction* AvoidAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Action", meta = (AllowPrivateAccess = "true"))
	UInputAction* MainAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Action", meta = (AllowPrivateAccess = "true"))
	UInputAction* EquipWeapon;

	/* ==================== HUD ==================== */

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Action", meta = (AllowPrivateAccess = "true"))
	UInputAction* InventoryOn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Action", meta = (AllowPrivateAccess = "true"))
	UInputAction* TechniqueOn;
};
