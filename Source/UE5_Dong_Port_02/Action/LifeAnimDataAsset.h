#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "../Character/LifeData.h"

#include "LifeAnimDataAsset.generated.h"

class UAnimMontage;

UCLASS()
class UE5_DONG_PORT_02_API ULifeAnimDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interaction Anim")
	TMap<EInteractionType, TObjectPtr<UAnimMontage>> InteractionAnim;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Work Anim")
	TMap<EWorkType, TObjectPtr<UAnimMontage>> WorkAnim;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Rest Anim")
	TMap<ERestType, TObjectPtr<UAnimMontage>> RestAnim;
};
