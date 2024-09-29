#pragma once

#include "CoreMinimal.h"
#include "Land/Prob/BaseProb.h"
#include "Bed.generated.h"

UCLASS()
class UE5_DONG_PORT_02_API ABed : public ABaseProb
{
	GENERATED_BODY()
	
protected:
	ABed();

public:
	virtual void Active(ABaseHuman* human);
	virtual void Deactive(ABaseHuman* human);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> GetUpAnim;

protected:
	FTimerHandle TimerHandle;
	UFUNCTION()
	void RecoveryCondition();
};
