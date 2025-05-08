#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "HittedAnimAsset.generated.h"

UENUM(BlueprintType)
enum class EPushedDirection : uint8
{
	E_Forward UMETA(DisplayName = "Forward"),
	E_Right UMETA(DisplayName = "Right"),
	E_Left UMETA(DisplayName = "Left"),
	E_Back UMETA(DisplayName = "Back")
};

UENUM(BlueprintType)
enum class EHumanHittedPoint : uint8
{
	E_None UMETA(Hidden),
	E_HighForward UMETA(DisplayName = "High Forward"),
	E_HighBack UMETA(DisplayName = "High Back"),
	E_HighLeft UMETA(DisplayName = "High Left"),
	E_HighRight UMETA(DisplayName = "High Right"),
	E_MidForward UMETA(DisplayName = "Mid Forward"),
	E_MidBack UMETA(DisplayName = "Mid Back"),
	E_MidLeft UMETA(DisplayName = "Mid Left"),
	E_MidRight UMETA(DisplayName = "Mid Right"),
	E_LowForward UMETA(DisplayName = "Low Forward"),
	E_LowBack UMETA(DisplayName = "Low Back"),
	E_LowLeft UMETA(DisplayName = "Low Left"),
	E_LowRight UMETA(DisplayName = "Low Right"),
	E_Max UMETA(Hidden),
};

UENUM(BlueprintType)
enum class EPushType : uint8
{
	E_None UMETA(Hidden),
	E_Push UMETA(DisplayName = "Push"),
	E_StrongPush UMETA(DisplayName = "Strong Push"),
	E_Max UMETA(Hidden)
};

UCLASS()
class UE5_DONG_PORT_02_API UHittedAnimAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<EPushedDirection, TObjectPtr<UAnimMontage>> PushedAnim;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<EPushedDirection, TObjectPtr<UAnimMontage>> StrongPushedAnim;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<EHumanHittedPoint, TObjectPtr<UAnimMontage>> HittedAnim;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<EHumanHittedPoint, TObjectPtr<UAnimMontage>> DeadAnim;
};
