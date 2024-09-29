#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "HittedAnimAsset.generated.h"

UENUM(BlueprintType)
enum class EHittedDirection : uint8
{
	E_Forward UMETA(DisplayName = "Forward"),
	E_Right UMETA(DisplayName = "Right"),
	E_Left UMETA(DisplayName = "Left"),
	E_Back UMETA(DisplayName = "Back")
};

UENUM(BlueprintType)
enum class EHittedType : uint8
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
	TMap<EHittedDirection, TObjectPtr<UAnimMontage>> PushedAnim;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<EHittedDirection, TObjectPtr<UAnimMontage>> StrongPushedAnim;
};
