#pragma once

#include "CoreMinimal.h"
#include "StatusData.generated.h"

UENUM(BlueprintType)
enum class EStateEffectType : uint8
{
	E_None UMETA(DisplayName = "None"),
	E_Freezing UMETA(DisplayName = "Freezing"),
	E_Burn UMETA(DisplayName = "Burn"),
	E_Max UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EStateType : uint8
{
	E_Idle UMETA(DisplayName = "Idle"),
	E_Attack UMETA(DisplayName = "Attack"),
	E_Avoid UMETA(DisplayName = "Avoid"),
	E_Hitted UMETA(DisplayName = "Hitted"),
	E_Dead UMETA(DisplayName = "Dead"),
	E_Max UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct FStatus
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Status")
	int Level = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Status")
	int MHP = 100;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Status")
	int HP = 100;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Status")
	int ATK = 10;
};

USTRUCT(BlueprintType)
struct FLifeStatus
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Life Status")
	int Hunger = 0; // 허기 (1 ~ 100)
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Life Status")
	int Belligerence = 0; // 호전성 (1 ~ 100)
};