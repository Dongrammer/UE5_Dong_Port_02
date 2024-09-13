#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_CheckInBuilding.generated.h"

UCLASS()
class UE5_DONG_PORT_02_API UBTDecorator_CheckInBuilding : public UBTDecorator
{
	GENERATED_BODY()
	
protected:
	UBTDecorator_CheckInBuilding();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
