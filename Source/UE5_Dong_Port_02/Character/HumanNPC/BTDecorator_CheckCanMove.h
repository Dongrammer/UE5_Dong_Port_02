#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_CheckCanMove.generated.h"

UCLASS()
class UE5_DONG_PORT_02_API UBTDecorator_CheckCanMove : public UBTDecorator
{
	GENERATED_BODY()

protected:
	UBTDecorator_CheckCanMove();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
