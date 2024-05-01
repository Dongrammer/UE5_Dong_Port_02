#pragma once

#include "CoreMinimal.h"
#include "ActionData.generated.h"

UENUM(BlueprintType)
enum class EGauntletAction : uint8
{
	E_None UMETA(Hidden),
	E_LeftJap_01 UMETA(DisplayName = "Left Jap 01"),
	E_RightJap_01 UMETA(DisplayName = "Right Jap 01"),
	E_Max
};

UENUM(BlueprintType)
enum class ESwordAction : uint8
{
	E_None UMETA(Hidden),
	E_Cutting_01 UMETA(DisplayName = "Cutting 01"),
	E_Cutting_02 UMETA(DisplayName = "Cutting 02"),
	E_Max
};