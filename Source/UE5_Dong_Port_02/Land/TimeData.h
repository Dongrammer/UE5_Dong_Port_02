#pragma once

#include "CoreMinimal.h"

#include "TimeData.generated.h"

UENUM(BlueprintType)
enum class EWeekType : uint8
{
	E_None UMETA(Hidden),
	E_Monday UMETA(DisplayName = "Monday"),
	E_TuesDay UMETA(DisplayName = "TuesDay"),
	E_WednesDay UMETA(DisplayName = "WednesDay"),
	E_ThursDay UMETA(DisplayName = "ThursDay"),
	E_Friday UMETA(DisplayName = "Friday"),
	E_SaturDay UMETA(DisplayName = "SaturDay"),
	E_SunDay UMETA(DisplayName = "SunDay"),
	E_Max UMETA(Hidden)
};

UENUM(BlueprintType)
enum class DayType : uint8
{
	E_None UMETA(Hidden),
	E_Morning UMETA(DisplayName = "Morning"),
	E_Afternoon UMETA(DisplayName = "Afternoon"),
	E_Evening UMETA(DisplayName = "Evening"),
	E_Night UMETA(DisplayName = "Night"),
	E_Max UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct FGlobalTime
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time", meta = (ClampMin = "0"))
	int64 CurrentDay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time", meta = (ClampMin = "0", ClampMax = "1440"))
	int32 CurrentTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
	EWeekType CurrentWeek;
};