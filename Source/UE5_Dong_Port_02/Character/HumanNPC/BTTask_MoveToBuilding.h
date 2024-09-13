#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_MoveToBuilding.generated.h"

UCLASS()
class UE5_DONG_PORT_02_API UBTTask_MoveToBuilding : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTTask_MoveToBuilding();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	FTimerHandle EndTimer;
};
