#pragma once

#include "CoreMinimal.h"
#include "StatusData.generated.h"

UENUM(BlueprintType)
enum class EStateEffectType : uint8
{
	E_None UMETA(Hidden),
	E_Normal UMETA(DisplayName = "Normal"),
	E_Max UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EStateType : uint8
{
	E_Idle UMETA(DisplayName = "Idle"),
	E_Attack UMETA(DisplayName = "Attack"),
	E_Avoid UMETA(DisplayName = "Avoid"),
	E_Hitted UMETA(DisplayName = "Hitted"),
	E_Dead UMETA(DisplayName = "Dead")
};

USTRUCT(BlueprintType)
struct FStatus
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Status")
	int MHP = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Status")
	int HP = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Status")
	int ATK = 1;
};