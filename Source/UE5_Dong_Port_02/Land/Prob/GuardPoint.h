#pragma once

#include "CoreMinimal.h"
#include "Land/Prob/BaseProb.h"
#include "GuardPoint.generated.h"

/*
	- ���� �ٹ��ڰ� �;߸� �����ǵ���
	- ActiveMeshIn Only
*/

UCLASS()
class UE5_DONG_PORT_02_API AGuardPoint : public ABaseProb
{
	GENERATED_BODY()

protected:
	AGuardPoint();

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<ABaseHuman> PrevHuman;
	FTimerHandle TimerHandle;

public:
	void Active(ABaseHuman* human) override;
	void PreActive(ABaseHuman* human) override;
	void Deactive(ABaseHuman* human) override;

	UFUNCTION()
	void CheckHumanNearby();
};
