#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EStateType : uint8
{
	E_None UMETA(Hidden),
	E_Normal UMETA(DisplayName = "Normal"),
	E_Max UMETA(Hidden)
};