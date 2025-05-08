#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_RunAway.generated.h"

UCLASS()
class UE5_DONG_PORT_02_API UBTT_RunAway : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTT_RunAway();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
