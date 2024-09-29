#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_InitBehavior.generated.h"

UCLASS()
class UE5_DONG_PORT_02_API UBTTask_InitBehavior : public UBTTaskNode
{
	GENERATED_BODY()

protected:
	UBTTask_InitBehavior();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
