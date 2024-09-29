#pragma once

#include "CoreMinimal.h"
#include "Land/Prob/BaseProb.h"
#include "Chair.generated.h"

/*
	- ActiveMeshIn Only
*/

UCLASS()
class UE5_DONG_PORT_02_API AChair : public ABaseProb
{
	GENERATED_BODY()

public:
	AChair();

	void Active(ABaseHuman* human) override;
	void Deactive(ABaseHuman* human) override;

protected:
	FTimerHandle TimerHandle;
	UFUNCTION()
	void RecoveryCondition();
};
