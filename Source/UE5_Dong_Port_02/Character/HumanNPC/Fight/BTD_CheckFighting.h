#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTD_CheckFighting.generated.h"

UCLASS()
class UE5_DONG_PORT_02_API UBTD_CheckFighting : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTD_CheckFighting();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
