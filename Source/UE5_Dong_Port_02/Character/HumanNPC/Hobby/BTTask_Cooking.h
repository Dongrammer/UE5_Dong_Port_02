#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Cooking.generated.h"

UCLASS()
class UE5_DONG_PORT_02_API UBTTask_Cooking : public UBTTaskNode
{
	GENERATED_BODY()

protected:
	UBTTask_Cooking();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
