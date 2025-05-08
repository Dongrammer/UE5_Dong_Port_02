#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Drinking.generated.h"

class AHumanNPC_AIController;
class AHumanNPC;
class AInn;

struct TaskMemoryDrinking
{
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<AHumanNPC_AIController> cont;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<AHumanNPC> npc;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<AInn> inn;
};

UCLASS()
class UE5_DONG_PORT_02_API UBTTask_Drinking : public UBTTaskNode
{
	GENERATED_BODY()

protected:
	UBTTask_Drinking();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual uint16 GetInstanceMemorySize() const override;
};
