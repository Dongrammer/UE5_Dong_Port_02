#pragma once

#include "CoreMinimal.h"
#include "ActionData.generated.h"

class ABaseAction;

UENUM(BlueprintType)
enum class EActionType : uint8
{
	E_None UMETA(Hidden),
	E_Gauntlet UMETA(DisplayName = "Gauntlet Action"),
	E_OneHandSword UMETA(DisplayName = "OneHandSword Action"),
	E_Max UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EActionPassiveType : uint8
{
	E_None UMETA(Hidden),
	E_SpeedUp UMETA(DisplayName = "Speed Up"),
	E_DamageUp UMETA(DisplayName = "Damage Up"),
	E_Max UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct FActionData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EActionType ActionType = EActionType::E_None;

	UPROPERTY(EditAnywhere, BlueprintreadOnly)
	uint8 ActionNumber = 0;
};


UENUM(BlueprintType)
enum class EDashAction : uint8
{
	E_None UMETA(Hidden),
	E_GA_Dash_Start UMETA(Hidden),
	E_GA_Dash_01 UMETA(DisplayName = "GA Dash 01"),
	E_GA_Dash_02 UMETA(DisplayName = "GA Dash 02"),
	E_GA_Dash_03 UMETA(DisplayName = "GA Dash 03"),
	E_GA_Dash_End UMETA(Hidden),
	E_OHSW_Dash_Start UMETA(Hidden),
	E_OHSW_Dash_01 UMETA(DisplayName = "OHSW Dash 01"),
	E_OHSW_Dash_End UMETA(Hidden),
	E_Max UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EGauntletAction : uint8
{
	E_None UMETA(Hidden),
	E_Left_01 UMETA(DisplayName = "Left 01"),
	E_Left_02 UMETA(DisplayName = "Left 02"),
	E_Right_01 UMETA(DisplayName = "Right 01"),
	E_Kick_01 UMETA(DisplayName = "Kick 01"),
	E_Kick_02 UMETA(DisplayName = "Kick 02"),
	E_Kick_03 UMETA(DisplayName = "Kick 03"),
	E_Max
};

UENUM(BlueprintType)
enum class ESwordAction : uint8
{
	E_None UMETA(Hidden),
	E_Equip UMETA(DisplayName = "Equip"),
	E_Unequip UMETA(DisplayName = "Unequip"),
	E_Attack_01 UMETA(DisplayName = "Attack 01"),
	E_Attack_02 UMETA(DisplayName = "Attack 02"),
	E_Attack_03 UMETA(DisplayName = "Attack 03"),
	E_Max
};

USTRUCT(BlueprintType)
struct FNodeInfoData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText NodeName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText NodeDescription;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 RequireTP = 0;
};

UENUM(BlueprintType)
enum class EActiveCollisionType : uint8
{
	E_None UMETA(Hidden),
	E_LeftPunch UMETA(DisplayName = "LeftPunch"),
	E_RightPunch UMETA(DisplayName = "RightPunch"),
	E_LeftKick UMETA(DisplayName = "LeftKick"),
	E_RightKick UMETA(DisplayName = "RightKick"),
	E_OneHandSword UMETA(DisplayName = "OneHandSword"),
	E_Max UMETA(Hidden)
};