#pragma once

#include "CoreMinimal.h"
#include "Land/Prob/BaseProb.h"
#include "RestWallPoint.generated.h"

UCLASS()
class UE5_DONG_PORT_02_API ARestWallPoint : public ABaseProb
{
	GENERATED_BODY()

public:
	ARestWallPoint();

	void Active(ABaseHuman* human) override;
	void Deactive(ABaseHuman* human) override;

protected:
	FTimerHandle TimerHandle;
	UFUNCTION()
	void RecoveryCondition();
};
