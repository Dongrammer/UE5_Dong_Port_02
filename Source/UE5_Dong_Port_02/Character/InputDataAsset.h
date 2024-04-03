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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAcces = "true"))
	UInputAction* MoveInput;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAcces = "true"))
	UInputAction* LookInput;

	/* ==================== Action ==================== */

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Action", meta = (AllowPrivateAcces = "true"))
	UInputAction* AvoidAction;
};
