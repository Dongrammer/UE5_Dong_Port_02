#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EAttachType : uint8
{
	E_None UMETA(Hidden),
	E_Holder UMETA(DisplayName = "Holder"),
	E_Handle UMETA(DisplayName = "Handle"),
	E_Max UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	E_None UMETA(Hidden),
	E_Gauntlet UMETA(DisplayName = "Gauntlet"),
	E_Sword UMETA(DisplayName = "Sword")
};