#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"

#include "../LifeData.h"

#include "BTDecorator_CheckBehavior.generated.h"

/**
 *
 */
UCLASS()
class UE5_DONG_PORT_02_API UBTDecorator_CheckBehavior : public UBTDecorator
{
	GENERATED_BODY()

protected:
	UBTDecorator_CheckBehavior();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EBehaviorType CheckType;

};
