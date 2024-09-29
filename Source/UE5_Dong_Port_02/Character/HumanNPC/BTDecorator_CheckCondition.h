#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "../LifeData.h"
#include "BTDecorator_CheckCondition.generated.h"

UCLASS()
class UE5_DONG_PORT_02_API UBTDecorator_CheckCondition : public UBTDecorator
{
	GENERATED_BODY()
	
protected:
	UBTDecorator_CheckCondition();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EConditionType, float> OverCondition;
};
