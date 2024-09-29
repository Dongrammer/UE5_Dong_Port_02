#pragma once

#include "CoreMinimal.h"
#include "LifeData.generated.h"

UENUM(BlueprintType)
enum class EInteractionType : uint8
{
	E_None UMETA(Hidden),
	E_OpenDoor UMETA(DisplayName = "Open Door"),
	E_Max UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EWorkType : uint8
{
	E_None UMETA(Hidden),
	E_UseAnvil UMETA(DisplayName = "Use Anvil"),
	E_Guard UMETA(DisplayName = "Guard"),
	E_ShopKeeper UMETA(DisplayName = "ShopKeeper"),
	E_Max UMETA(Hidden)
};

UENUM(BlueprintType)
enum class ERestType : uint8
{
	E_None UMETA(Hidden),
	E_Seet UMETA(DisplayName = "Seet"),
	E_Sleep UMETA(DisplayName = "Sleep"),
	E_Max UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EBehaviorType : uint8
{
	E_None UMETA(Hidden),
	E_Working UMETA(DisplayName = "Working"),
	E_Resting UMETA(DisplayName = "Resting"),
	E_Max UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EConditionType : uint8
{
	E_None UMETA(Hidden),
	E_Fatigue UMETA(DisplayName = "Fatigue"),
	E_Max UMETA(Hidden)
};