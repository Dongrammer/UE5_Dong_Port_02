#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EGauntletAction : uint8
{
	E_None UMETA(Hidden),
	E_LeftJap_01 UMETA(DisplayName = "Left Jap 01"),
	E_RightJap_01 UMETA(DisplayName = "Right Jap 01"),
	E_Max
};