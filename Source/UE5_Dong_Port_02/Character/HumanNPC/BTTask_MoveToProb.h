#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_MoveToProb.generated.h"

class ABaseProb;

UCLASS()
class UE5_DONG_PORT_02_API UBTTask_MoveToProb : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTTask_MoveToProb();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
//
//private:
//	TObjectPtr<ABaseProb> SelectedProb;
};
