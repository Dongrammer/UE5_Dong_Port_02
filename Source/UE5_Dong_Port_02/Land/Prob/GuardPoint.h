#pragma once

#include "CoreMinimal.h"
#include "Land/Prob/BaseProb.h"
#include "GuardPoint.generated.h"

/* 
	- 교대 시간을 위해 다음 근무자와 출퇴근 시간을 10분 정도 조정 
	- ActiveMeshIn Only
*/

UCLASS()
class UE5_DONG_PORT_02_API AGuardPoint : public ABaseProb
{
	GENERATED_BODY()
	
protected:
	AGuardPoint();

	TObjectPtr<ABaseHuman> PrevHuman;
	FTimerHandle TimerHandle;

public:
	void Active(ABaseHuman* human) override;
	void PreActive(ABaseHuman* human) override;
	void Deactive(ABaseHuman* human) override;

	UFUNCTION()
	void CheckHumanNearby();
};
